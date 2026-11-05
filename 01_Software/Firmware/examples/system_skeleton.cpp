#include <Arduino.h>
#include "Interfaces.h"
#include "StubDevices.h"
#include "ControlTypes.h"
#include "SampleTimer.h"

// Compile-only integration skeleton. Never drives actuators.
StubMotorDriver hipLeftMotor, kneeLeftMotor, hipRightMotor, kneeRightMotor;
StubImuSensor torsoImu;
StubFootSensor leftFoot, rightFoot;
StubJointSensor hipLeftAngle, kneeLeftAngle, hipRightAngle, kneeRightAngle;
SystemMode mode = SystemMode::DISABLED;
SampleTimer timer(20); // 50 Hz demonstration loop, not a validated control rate

void setup() {
  Serial.begin(115200);
  hipLeftMotor.disable();
  kneeLeftMotor.disable();
  hipRightMotor.disable();
  kneeRightMotor.disable();
  // Placeholder devices intentionally fail initialization.
  bool ready = torsoImu.begin() && leftFoot.begin() && rightFoot.begin()
    && hipLeftAngle.begin() && kneeLeftAngle.begin()
    && hipRightAngle.begin() && kneeRightAngle.begin()
    && hipLeftMotor.begin() && kneeLeftMotor.begin()
    && hipRightMotor.begin() && kneeRightMotor.begin();
  mode = ready ? SystemMode::READY : SystemMode::DISABLED;
}
void loop() {
  if (!timer.due(millis())) return;
  SafetyInputs safety{}; // Defaults prevent activation.
  if (!canActivate(safety)) {
    mode = SystemMode::DISABLED;
    hipLeftMotor.disable();
    kneeLeftMotor.disable();
    hipRightMotor.disable();
    kneeRightMotor.disable();
  }
  static uint32_t lastPrint = 0;
  if (millis() - lastPrint >= 1000) {
    lastPrint = millis();
    Serial.println("SKELETON ONLY: actuator commands disabled");
  }
}
