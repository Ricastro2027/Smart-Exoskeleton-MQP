#pragma once
#include <Arduino.h>
enum class SystemMode : uint8_t { DISABLED, READY, ACTIVE, FAULT };
struct ControlRequest {
  float hipLeftDeg = NAN;
  float kneeLeftDeg = NAN;
  float hipRightDeg = NAN;
  float kneeRightDeg = NAN;
};
struct SafetyInputs {
  bool hardwarePowerCutoffVerified = false;
  bool sensorsValid = false;
  bool driversHealthy = false;
  bool explicitEnable = false;
};
inline bool canActivate(const SafetyInputs &s) {
  return s.hardwarePowerCutoffVerified && s.sensorsValid &&
         s.driversHealthy && s.explicitEnable;
}
