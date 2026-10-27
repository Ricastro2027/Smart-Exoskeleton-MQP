#include <Arduino.h>
#include "PinConfig.h"
void setup() { Serial.begin(115200); pinMode(Pins::ENABLE_BUTTON, INPUT_PULLUP); }
void loop() {
  Serial.println(digitalRead(Pins::ENABLE_BUTTON) == LOW ? "PRESSED" : "RELEASED");
  delay(100);
}
