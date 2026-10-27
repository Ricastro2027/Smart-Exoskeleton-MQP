#pragma once
#include <Arduino.h>
// Provisional pin map from the October 26 sensor prototype.
// Teensy 4.1 I2C Wire uses physical pins 18 (SDA) and 19 (SCL).
// Analog inputs must stay within 0-3.3 V.
namespace Pins {
constexpr int BATTERY_OPTIONAL = A0; // unconfigured; do not connect until divider is designed
constexpr int FOOT_LEFT_HEEL = A1;
constexpr int FOOT_LEFT_FORE = A2;
constexpr int FOOT_RIGHT_HEEL = A3;
constexpr int FOOT_RIGHT_FORE = A11;
constexpr int THIGH_LEFT = A12;
constexpr int THIGH_RIGHT = A6;
constexpr int POT_HIP_LEFT = A7;
constexpr int POT_KNEE_LEFT = A8;
constexpr int POT_HIP_RIGHT = A9;
constexpr int POT_KNEE_RIGHT = A10;
constexpr int ENABLE_BUTTON = 6; // START, active low; not an E-stop
constexpr int BUZZER = 7; // external 3.3 V-compatible driver required
constexpr int MODE_HIGH = 3;
constexpr int MODE_MEDIUM = 4;
constexpr int MODE_ECO = 5;
constexpr uint8_t IMU_MUX_ADDR = 0x70;
}
