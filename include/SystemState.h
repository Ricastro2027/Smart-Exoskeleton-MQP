#pragma once
#include <Arduino.h>
// States describe firmware supervision, not proof of hardware safety.
enum class ExoState : uint8_t { BOOT, WAIT_FOR_START, CALIBRATING, MONITORING, FAULT };
inline const char* stateName(ExoState s) {
  switch (s) {
    case ExoState::BOOT: return "BOOT";
    case ExoState::WAIT_FOR_START: return "WAIT_FOR_START";
    case ExoState::CALIBRATING: return "CALIBRATING";
    case ExoState::MONITORING: return "MONITORING";
    case ExoState::FAULT: return "FAULT";
  }
  return "UNKNOWN";
}
