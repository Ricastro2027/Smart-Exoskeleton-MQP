/*
  WPI Lower-Limb Exoskeleton - SENSOR-ONLY RESEARCH PROTOTYPE
  Teensy 4.1 / Arduino IDE
  Requires: Adafruit MPU6050, Adafruit Unified Sensor, Adafruit BusIO
  Four MPU6050s via TCA9548A I2C multiplexer (channels 0-3).

  NOT A WEARABLE CONTROLLER. NO MOTOR OUTPUTS OR ARMING CAPABILITY.
  All calibration constants, safety thresholds and wiring require verification.
  No independent E-stop, driver enable, clutch or battery protection is implemented.
*/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

constexpr uint32_t LOOP_US = 5000;   // Target 200 Hz, not a hard guarantee
constexpr uint32_t TELEMETRY_MS = 100;
constexpr uint32_t CALIBRATION_MS = 3000;
constexpr uint8_t MUX_ADDR = 0x70;
constexpr uint8_t IMU_COUNT = 4;
constexpr uint8_t ADC_BITS = 12;
constexpr int ADC_MAX = (1 << ADC_BITS) - 1;

// Physical Teensy 4.1 pins 18/19 are I2C SDA/SCL, so do NOT use A4/A5 there.
// Original right forefoot and left thigh inputs are reassigned to A11/A12.
constexpr uint8_t PIN_BATTERY = A0;       // Physical 14, OPTIONAL; uncalibrated
constexpr uint8_t PIN_LEFT_HEEL = A1;     // Physical 15
constexpr uint8_t PIN_LEFT_FORE = A2;     // Physical 16
constexpr uint8_t PIN_RIGHT_HEEL = A3;    // Physical 17
constexpr uint8_t PIN_RIGHT_FORE = A11;   // Physical 26, formerly A4
constexpr uint8_t PIN_LEFT_THIGH = A12;   // Physical 27, formerly A5
constexpr uint8_t PIN_RIGHT_THIGH = A6;   // Physical 20
constexpr uint8_t PIN_LEFT_HIP = A7;      // Physical 21
constexpr uint8_t PIN_LEFT_KNEE = A8;     // Physical 22
constexpr uint8_t PIN_RIGHT_HIP = A9;     // Physical 23
constexpr uint8_t PIN_RIGHT_KNEE = A10;   // Physical 24
constexpr uint8_t PIN_START = 6;         // Ground to request baseline calibration
constexpr uint8_t PIN_BUZZER = 7;        // 3.3 V-compatible buzzer driver only
constexpr uint8_t PIN_MODE_HIGH = 3;
constexpr uint8_t PIN_MODE_MED = 4;
constexpr uint8_t PIN_MODE_ECO = 5;

// Configure these after measuring each joint's mechanical range.
// Until then, angles are NOT trusted or reported in degrees.
struct PotCalibration {
  int rawAtMin;
  int rawAtMax;
  float minDeg;
  float maxDeg;
  bool verified;
};
PotCalibration potCal[4] = {
  {0, ADC_MAX, 0, 0, false}, // left hip
  {0, ADC_MAX, 0, 0, false}, // left knee
  {0, ADC_MAX, 0, 0, false}, // right hip
  {0, ADC_MAX, 0, 0, false}, // right knee
};

// Placeholders: change only after actual drivetrain selection and validation.
struct DrivetrainPlaceholder {
  float reduction;
  bool validated;
};
DrivetrainPlaceholder drivetrain[4] = {
  {25.0f, false}, {25.0f, false}, {25.0f, false}, {25.0f, false}
};

// Battery chemistry, divider ratio, and low-voltage limits are NOT selected.
// Do not infer a voltage or use this input as a safety cutoff yet.
constexpr bool BATTERY_MONITOR_CONFIGURED = false;

// Thresholds are placeholders only; raw values are printed for empirical setup.
constexpr bool FOOT_THRESHOLDS_CALIBRATED = false;
int footOn[4] = {2200, 2200, 2200, 2200};
int footOff[4] = {1800, 1800, 1800, 1800};

// These FSRs detect cuff pressure change, NOT EMG or validated muscle intent.
constexpr float PRESSURE_FILTER_ALPHA = 0.15f;
constexpr uint8_t imuChannels[IMU_COUNT] = {0, 1, 2, 3};
const char *imuNames[IMU_COUNT] = {"left_thigh", "left_shank", "right_thigh", "right_shank"};
Adafruit_MPU6050 imu;

struct IMUReading {
  float ax, ay, az, gx, gy, gz;
  bool valid;
};
IMUReading imus[IMU_COUNT] = {};

struct SensorReadings {
  int foot[4];
  int thigh[2];
  int pot[4];
  int batteryRaw;
} readings = {};

float pressureFiltered[2] = {};
float pressureBaseline[2] = {};
float calibrationSum[2] = {};
uint32_t calibrationSamples = 0;
bool footContact[4] = {};

enum class State { BOOT, WAIT_CALIBRATION, CALIBRATING, MONITORING, FAULT };
enum class Mode { MODE_HIGH, MODE_MEDIUM, MODE_ECO, INVALID };
State state = State::BOOT;
Mode mode = Mode::INVALID;
uint32_t nextTick = 0;
uint32_t lastTelemetry = 0;
uint32_t calibrationStart = 0;
uint32_t overrunCount = 0;
uint32_t consecutiveOverruns = 0;
uint32_t imuErrors = 0;
const char *faultReason = "none";

bool selectMux(uint8_t channel) {
  if (channel >= 8) return false;
  Wire.beginTransmission(MUX_ADDR);
  Wire.write(static_cast<uint8_t>(1u << channel));
  return Wire.endTransmission() == 0;
}

bool initIMUs() {
  for (uint8_t i = 0; i < IMU_COUNT; ++i) {
    if (!selectMux(imuChannels[i])) return false;
    if (!imu.begin(0x68, &Wire)) return false;
    imu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  }
  return true;
}

bool readIMUs() {
  bool allValid = true;
  for (uint8_t i = 0; i < IMU_COUNT; ++i) {
    imus[i].valid = false;
    if (!selectMux(imuChannels[i])) { allValid = false; ++imuErrors; continue; }
    sensors_event_t a, g, t;
    if (!imu.getEvent(&a, &g, &t)) { allValid = false; ++imuErrors; continue; }
    imus[i] = {a.acceleration.x, a.acceleration.y, a.acceleration.z,
               g.gyro.x, g.gyro.y, g.gyro.z, true};
  }
  return allValid;
}

void readAnalogs() {
  readings.foot[0] = analogRead(PIN_LEFT_HEEL);
  readings.foot[1] = analogRead(PIN_LEFT_FORE);
  readings.foot[2] = analogRead(PIN_RIGHT_HEEL);
  readings.foot[3] = analogRead(PIN_RIGHT_FORE);
  readings.thigh[0] = analogRead(PIN_LEFT_THIGH);
  readings.thigh[1] = analogRead(PIN_RIGHT_THIGH);
  readings.pot[0] = analogRead(PIN_LEFT_HIP);
  readings.pot[1] = analogRead(PIN_LEFT_KNEE);
  readings.pot[2] = analogRead(PIN_RIGHT_HIP);
  readings.pot[3] = analogRead(PIN_RIGHT_KNEE);
  readings.batteryRaw = analogRead(PIN_BATTERY);
  for (int i = 0; i < 2; ++i)
    pressureFiltered[i] += PRESSURE_FILTER_ALPHA * (readings.thigh[i] - pressureFiltered[i]);
  if (FOOT_THRESHOLDS_CALIBRATED) {
    for (int i = 0; i < 4; ++i) {
      if (!footContact[i] && readings.foot[i] >= footOn[i]) footContact[i] = true;
      if (footContact[i] && readings.foot[i] <= footOff[i]) footContact[i] = false;
    }
  }
}

Mode readMode() {
  const bool h = digitalRead(PIN_MODE_HIGH) == LOW;
  const bool m = digitalRead(PIN_MODE_MED) == LOW;
  const bool e = digitalRead(PIN_MODE_ECO) == LOW;
  if (static_cast<int>(h) + static_cast<int>(m) + static_cast<int>(e) != 1)
    return Mode::INVALID;
  return h ? Mode::MODE_HIGH : (m ? Mode::MODE_MEDIUM : Mode::MODE_ECO);
}

const char *stateName(State s) {
  switch (s) {
    case State::BOOT: return "BOOT";
    case State::WAIT_CALIBRATION: return "WAIT_CALIBRATION";
    case State::CALIBRATING: return "CALIBRATING";
    case State::MONITORING: return "MONITORING";
    default: return "FAULT";
  }
}

void enterFault(const char *reason) {
  state = State::FAULT;
  faultReason = reason;
  // NO motor outputs exist in this prototype. A real system requires independent
  // hardware stop, driver disable, watchdog and verified fault response.
  digitalWrite(PIN_BUZZER, LOW);
  Serial.print("FAULT: "); Serial.println(faultReason);
}

void printTelemetry() {
  Serial.print("state:"); Serial.print(stateName(state));
  Serial.print(",mode:"); Serial.print(static_cast<int>(mode));
  Serial.print(",foot_raw:");
  for (int i = 0; i < 4; ++i) { Serial.print(readings.foot[i]); Serial.print(i == 3 ? ',' : '/'); }
  Serial.print("thigh_delta:");
  for (int i = 0; i < 2; ++i) {
    Serial.print(pressureFiltered[i] - pressureBaseline[i], 1);
    Serial.print(i == 1 ? ',' : '/');
  }
  Serial.print("pot_raw:");
  for (int i = 0; i < 4; ++i) { Serial.print(readings.pot[i]); Serial.print(i == 3 ? ',' : '/'); }
  Serial.print("imu_valid:");
  for (int i = 0; i < 4; ++i) Serial.print(imus[i].valid ? '1' : '0');
  Serial.print(",battery_adc:"); Serial.print(readings.batteryRaw);
  Serial.print(",overruns:"); Serial.print(overrunCount);
  Serial.print(",imu_errors:"); Serial.println(imuErrors);
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(ADC_BITS);
  pinMode(PIN_START, INPUT_PULLUP);
  pinMode(PIN_MODE_HIGH, INPUT_PULLUP);
  pinMode(PIN_MODE_MED, INPUT_PULLUP);
  pinMode(PIN_MODE_ECO, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
  Wire.begin();
  Wire.setClock(400000);
  if (!initIMUs()) {
    enterFault("I2C multiplexer or MPU6050 initialization failed");
  } else {
    state = State::WAIT_CALIBRATION;
    Serial.println("SENSOR-ONLY PROTOTYPE: motor actuation is unavailable.");
    Serial.println("Press START to collect 3 seconds of stationary cuff baseline.");
  }
  nextTick = micros() + LOOP_US;
}

void loop() {
  const uint32_t now = micros();
  if (static_cast<int32_t>(now - nextTick) < 0) return;
  const uint32_t tickStart = micros();
  nextTick += LOOP_US;
  if (static_cast<int32_t>(tickStart - nextTick) >= 0) {
    ++overrunCount;
    ++consecutiveOverruns;
    nextTick = tickStart + LOOP_US; // Resynchronize instead of running a backlog
  } else {
    consecutiveOverruns = 0;
  }
  if (state != State::FAULT) {
    readAnalogs();
    mode = readMode();
    if (mode == Mode::INVALID) {
      // Modes are DISPLAY ONLY; no motion can be enabled.
    }
    if (!readIMUs()) enterFault("IMU read failure");
    if (consecutiveOverruns >= 10) enterFault("Repeated scheduling overruns");
    if (state == State::WAIT_CALIBRATION && digitalRead(PIN_START) == LOW) {
      calibrationStart = millis();
      calibrationSamples = 0;
      calibrationSum[0] = calibrationSum[1] = 0;
      state = State::CALIBRATING;
    }
    if (state == State::CALIBRATING) {
      for (int i = 0; i < 2; ++i) calibrationSum[i] += readings.thigh[i];
      ++calibrationSamples;
      if (millis() - calibrationStart >= CALIBRATION_MS) {
        if (calibrationSamples == 0) enterFault("Calibration samples missing");
        else {
          for (int i = 0; i < 2; ++i) {
            pressureBaseline[i] = calibrationSum[i] / calibrationSamples;
            pressureFiltered[i] = pressureBaseline[i];
          }
          state = State::MONITORING;
          Serial.println("Calibration complete. Monitoring only. Motors remain disabled.");
        }
      }
    }
  }
  if (millis() - lastTelemetry >= TELEMETRY_MS) {
    lastTelemetry = millis();
    if (Serial.availableForWrite() >= 64) printTelemetry();
  }
  if (static_cast<int32_t>(micros() - nextTick) >= 0) {
    ++overrunCount;
    ++consecutiveOverruns;
  }
}