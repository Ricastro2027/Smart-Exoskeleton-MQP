#include "Arduino.h"
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

void Motor_Effort_Adjust() {


    range = Calculate_Range(); %adjust the sensitivity based on FSR reading range
    maximum = range * 0.8; % set the target muscle force to 80% of the range
    %%%% ^ ADJUST IF NECESSARY ^ %%%%

    new_reading = analogRead(FSR_PIN); %read the FSR sensor value
    


    if Muscle_Force > 0.5 {
        // Increase motor output
    } else if Muscle_Force < 0.5 {
        // Decrease motor output
    } else {
        // Maintain current motor output
    }

}

void FSR_Record() {
    %% FSR_PIN = A0; %define the FSR pin

    catalog = [];
    if len(catalog) >= 100 {
        return catalog; %return the catalog if it has 100 readings
    } else{
      Reading = analogRead(FSR_PIN); %read the FSR sensor value
      catalog.append(Reading);
    }
  }

void Calculate_Range() {
    catalog = FSR_Record(); %call the FSR_Record function to get the readings

    if len(catalog) <= 0 {
        return 0; % return 0 if there are no readings
    } else {
        min = min(catalog); %find the minimum reading
        max = max(catalog); %find the maximum reading
        range = (max - min); %calculate the range of analog readings
        return range;
    }
}