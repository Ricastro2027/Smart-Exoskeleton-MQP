#include <Arduino.h>
#include "PinConfig.h"
#include "AnalogSensor.h"
#include "JointCalibration.h"
#include "SampleTimer.h"
// PLACEHOLDER VALUES FOR SOFTWARE DEMONSTRATION ONLY.
// Replace after measuring actual raw counts and physical joint angles.
JointCalibration calibration{500, 3500, 0.0f, 90.0f};
AnalogSensor sensor(Pins::POT_KNEE_LEFT);
SampleTimer timer(100);
void setup() { Serial.begin(115200); analogReadResolution(12); sensor.begin(); }
void loop() {
  if (!timer.due(millis())) return;
  uint16_t raw = sensor.readRaw();
  Serial.print("raw="); Serial.print(raw);
  Serial.print(", calibration_valid="); Serial.print(calibration.valid());
  Serial.print(", inside_calibrated_range="); Serial.print(calibration.inRange(raw));
  Serial.print(", example_degrees="); Serial.println(calibration.angleDegrees(raw), 2);
}
