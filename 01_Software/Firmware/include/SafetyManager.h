#pragma once
#include <Arduino.h>
// Software fault latching is a diagnostic layer, NOT an independent E-stop.
// No motor output may be enabled by this class.
enum class FaultCode : uint8_t { NONE, ESTOP_REQUEST, SENSOR_FAULT, TIMING_FAULT, MOTOR_FAULT };
class SafetyManager {
 public:
  void begin() { fault_ = FaultCode::NONE; }
  void trip(FaultCode reason) {
    if (reason != FaultCode::NONE && fault_ == FaultCode::NONE) fault_ = reason;
  }
  bool faulted() const { return fault_ != FaultCode::NONE; }
  FaultCode fault() const { return fault_; }
  bool motorPermission() const { return false; } // fail closed until validated hardware integration
  // Deliberately no automatic reset. Power cycle is not a substitute for
  // hardware E-stop reset and a separately validated restart procedure.
 private:
  FaultCode fault_ = FaultCode::NONE;
};
