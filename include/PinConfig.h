#pragma once
// Initial bench-test pin assignments. Verify wiring before connecting hardware.
namespace Pins {
constexpr int POT_HIP_LEFT = A0;
constexpr int POT_KNEE_LEFT = A1;
constexpr int POT_HIP_RIGHT = A2;
constexpr int POT_KNEE_RIGHT = A3;
constexpr int ENABLE_BUTTON = 2; // Momentary switch to GND, INPUT_PULLUP
}
