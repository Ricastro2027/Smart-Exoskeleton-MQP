#pragma once
#include <Arduino.h>
// Calibration must be measured for each installed joint; do not assume a 0-90 degree range.
struct JointCalibration {
  uint16_t rawMin;
  uint16_t rawMax;
  float degreesAtMin;
  float degreesAtMax;
  bool valid() const { return rawMax > rawMin && degreesAtMax != degreesAtMin; }
  bool inRange(uint16_t raw) const { return valid() && raw >= rawMin && raw <= rawMax; }
  float degrees(uint16_t reading) const {
    if (!valid()) return NAN;
    return degreesAtMin + (float(reading - rawMin) / float(rawMax - rawMin)) * (degreesAtMax - degreesAtMin);
  }
};
