#pragma once
#include <Arduino.h>
// Bench-test heuristics only; not safety-rated fault detection.
struct SensorHealth {
  static bool withinAdcRange(uint16_t raw, uint16_t low = 8, uint16_t high = 4087) {
    return raw >= low && raw <= high;
  }
  static bool fresh(uint32_t nowMs, uint32_t lastUpdateMs, uint32_t maxAgeMs) {
    return uint32_t(nowMs - lastUpdateMs) <= maxAgeMs;
  }
};
