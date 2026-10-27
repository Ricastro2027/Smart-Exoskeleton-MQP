#include <Arduino.h>
#include "PinConfig.h"
#include "SystemState.h"
#include "SafetyManager.h"

// Sensor-only bench monitor. This firmware does NOT control motor drivers.
// E-stop is not wired/configured yet; a separate hardware safety circuit is mandatory.
SafetyManager safety;
ExoState state = ExoState::BOOT;

void setup() {
  Serial.begin(115200);
  pinMode(Pins::ENABLE_BUTTON, INPUT_PULLUP);
  analogReadResolution(12);
  safety.begin();
  state = ExoState::WAIT_FOR_START;
}

void loop() {
  // A fault, once latched, prevents progression. No motor outputs exist.
  if (safety.faulted()) state = ExoState::FAULT;
  static uint32_t lastPrint = 0;
  if (millis() - lastPrint >= 100) {
    lastPrint = millis();
    Serial.print("state=");
    Serial.print(stateName(state));
    Serial.print(", motor_permission=");
    Serial.print(safety.motorPermission() ? 1 : 0);
    Serial.print(", hipL_raw=");
    Serial.print(analogRead(Pins::POT_HIP_LEFT));
    Serial.print(", kneeL_raw=");
    Serial.print(analogRead(Pins::POT_KNEE_LEFT));
    Serial.print(", hipR_raw=");
    Serial.print(analogRead(Pins::POT_HIP_RIGHT));
    Serial.print(", kneeR_raw=");
    Serial.print(analogRead(Pins::POT_KNEE_RIGHT));
    Serial.print(", start_pressed=");
    Serial.println(digitalRead(Pins::ENABLE_BUTTON) == LOW ? 1 : 0);
  }
}
