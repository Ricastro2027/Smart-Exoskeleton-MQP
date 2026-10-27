#include <Arduino.h>
#include "PinConfig.h"
#include "AnalogSensor.h"
#include "SensorHealth.h"
#include "SampleTimer.h"
AnalogSensor sensor(Pins::POT_HIP_LEFT);
SampleTimer timer(100);
void setup() { Serial.begin(115200); analogReadResolution(12); sensor.begin(); }
void loop() {
  if (!timer.due(millis())) return;
  uint16_t raw = sensor.readRaw();
  Serial.print("raw="); Serial.print(raw);
  Serial.print(", fraction="); Serial.print(AnalogSensor::normalized(raw), 3);
  Serial.print(", adc_rail_warning="); Serial.println(!SensorHealth::withinAdcRange(raw));
}
