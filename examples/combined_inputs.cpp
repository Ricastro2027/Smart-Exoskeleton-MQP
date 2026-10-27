#include <Arduino.h>
#include "PinConfig.h"
void setup() { Serial.begin(115200); pinMode(Pins::ENABLE_BUTTON, INPUT_PULLUP); analogReadResolution(12); }
void loop() {
  Serial.print("pot_raw=");
  Serial.print(analogRead(Pins::POT_HIP_LEFT));
  Serial.print(", button_pressed=");
  Serial.println(digitalRead(Pins::ENABLE_BUTTON) == LOW ? 1 : 0);
  delay(100);
}
