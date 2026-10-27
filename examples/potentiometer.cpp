#include <Arduino.h>
#include "PinConfig.h"
void setup() { Serial.begin(115200); analogReadResolution(12); }
void loop() {
  Serial.print("hip_left_raw=");
  Serial.println(analogRead(Pins::POT_HIP_LEFT));
  delay(100);
}
