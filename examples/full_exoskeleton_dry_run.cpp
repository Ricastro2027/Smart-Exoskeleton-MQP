/* WPI exoskeleton: integrated DRY RUN, Teensy 4.1.
   Four IMUs via TCA9548A, 4 foot FSRs, 2 thigh cuff FSRs,
   4 joint potentiometers, mode selector. No actuation.
   Requires Adafruit MPU6050 / Unified Sensor / BusIO.
   Not a wearable controller; safety, calibration and motor interface TBD.
*/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

constexpr uint32_t PERIOD_US = 5000; // nominal 200 Hz
constexpr uint8_t MUX = 0x70;
constexpr uint8_t N_IMU = 4, N_JOINT = 4;
constexpr uint8_t footPins[4] = {A1,A2,A3,A11};
constexpr uint8_t thighPins[2] = {A12,A6};
constexpr uint8_t potPins[4] = {A7,A8,A9,A10};
constexpr uint8_t modePins[3] = {3,4,5};
constexpr uint8_t START_PIN = 6;
Adafruit_MPU6050 imu;

struct JointState { uint16_t potRaw; float targetDeg; bool angleCalibrated; };
JointState joints[N_JOINT] = {};
struct LegState { uint16_t heel, forefoot, thigh; float cuffDelta; bool contactCalibrated; };
LegState legs[2] = {};
float baseline[2] = {}, baselineSum[2] = {};
uint32_t baselineCount = 0, baselineStart = 0;
uint32_t nextTick = 0, lastPrint = 0, missed = 0;
bool imuOK[N_IMU] = {};

enum State { WAIT_FOR_START, CALIBRATE, MONITOR, FAULT };
State state = WAIT_FOR_START;
const char *fault = "none";

bool selectIMU(uint8_t channel) {
  Wire.beginTransmission(MUX);
  Wire.write((uint8_t)(1u << channel));
  return Wire.endTransmission() == 0;
}

bool pollIMUs() {
  for (uint8_t i = 0; i < N_IMU; ++i) {
    if (!selectIMU(i)) { imuOK[i] = false; return false; }
    sensors_event_t a,g,t;
    imuOK[i] = imu.getEvent(&a,&g,&t);
    if (!imuOK[i]) return false;
    // Orientation and joint-angle fusion are intentionally NOT invented here.
  }
  return true;
}

int readMode() {
  int selected = -1, count = 0;
  for (int i = 0; i < 3; ++i)
    if (digitalRead(modePins[i]) == LOW) { selected = i; ++count; }
  return count == 1 ? selected : -1;
}

void sampleSensors() {
  legs[0].heel = analogRead(footPins[0]);
  legs[0].forefoot = analogRead(footPins[1]);
  legs[1].heel = analogRead(footPins[2]);
  legs[1].forefoot = analogRead(footPins[3]);
  for (int i = 0; i < 2; ++i) {
    legs[i].thigh = analogRead(thighPins[i]);
    legs[i].cuffDelta = legs[i].thigh - baseline[i];
  }
  for (int j = 0; j < N_JOINT; ++j) joints[j].potRaw = analogRead(potPins[j]);
}

void report() {
  Serial.print("state="); Serial.print((int)state);
  Serial.print(" mode="); Serial.print(readMode());
  Serial.print(" foot=");
  for (int i = 0; i < 2; ++i) {
    Serial.print(legs[i].heel); Serial.print('/'); Serial.print(legs[i].forefoot);
    if (i == 0) Serial.print(',');
  }
  Serial.print(" cuff_delta="); Serial.print(legs[0].cuffDelta);
  Serial.print('/'); Serial.print(legs[1].cuffDelta);
  Serial.print(" pot_raw=");
  for (int j = 0; j < N_JOINT; ++j) {
    Serial.print(joints[j].potRaw);
    if (j != N_JOINT-1) Serial.print('/');
  }
  Serial.print(" missed="); Serial.print(missed);
  Serial.print(" motor_output=DISABLED fault="); Serial.println(fault);
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  pinMode(START_PIN, INPUT_PULLUP);
  for (int i = 0; i < 3; ++i) pinMode(modePins[i], INPUT_PULLUP);
  Wire.begin(); Wire.setClock(400000);
  for (uint8_t i = 0; i < N_IMU; ++i) {
    if (!selectIMU(i) || !imu.begin(0x68, &Wire)) {
      state = FAULT; fault = "IMU initialization failed"; break;
    }
    imu.setFilterBandwidth(MPU6050_BANDWIDTH_21_HZ);
  }
  Serial.println("INTEGRATED DRY RUN ONLY. NO MOTOR OUTPUTS.");
  nextTick = micros() + PERIOD_US;
}

void loop() {
  if ((int32_t)(micros() - nextTick) < 0) return;
  nextTick += PERIOD_US;
  if ((int32_t)(micros() - nextTick) >= 0) { ++missed; nextTick = micros() + PERIOD_US; }
  if (state != FAULT) {
    sampleSensors();
    if (!pollIMUs()) { state = FAULT; fault = "IMU polling failed"; }
    if (state == WAIT_FOR_START && digitalRead(START_PIN) == LOW) {
      baselineStart = millis(); baselineCount = 0;
      baselineSum[0] = baselineSum[1] = 0;
      state = CALIBRATE;
    }
    if (state == CALIBRATE) {
      for (int i = 0; i < 2; ++i) baselineSum[i] += legs[i].thigh;
      ++baselineCount;
      if (millis() - baselineStart >= 3000) {
        for (int i = 0; i < 2; ++i) baseline[i] = baselineSum[i] / baselineCount;
        state = MONITOR;
      }
    }
    // Planned later: calibrated joint angles, validated gait phases,
    // assistance-as-needed, verified driver interfaces and safety system.
    // Motor control deliberately absent, even in MONITOR state.
  }
  if (millis() - lastPrint >= 100) { lastPrint = millis(); report(); }
}