#include <Arduino.h>
#include "PinConfig.h"

// Safe default: monitoring only. No motor output is configured.
void setup() {
  Serial.begin(115200);
  pinMode(Pins::ENABLE_BUTTON, INPUT_PULLUP);
  analogReadResolution(12);
}
void loop() {
  static uint32_t lastPrint = 0;
  if (millis() - lastPrint >= 100) {
    lastPrint = millis();
    Serial.print("hipL_raw=");
    Serial.print(analogRead(Pins::POT_HIP_LEFT));
    Serial.print(", kneeL_raw=");
    Serial.print(analogRead(Pins::POT_KNEE_LEFT));
    Serial.print(", hipR_raw=");
    Serial.print(analogRead(Pins::POT_HIP_RIGHT));
    Serial.print(", kneeR_raw=");
    Serial.print(analogRead(Pins::POT_KNEE_RIGHT));
    Serial.print(", button_pressed=");
    Serial.println(digitalRead(Pins::ENABLE_BUTTON) == LOW ? 1 : 0);
  }
}
