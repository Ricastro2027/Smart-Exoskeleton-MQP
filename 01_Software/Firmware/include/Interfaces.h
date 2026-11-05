#pragma once
#include <Arduino.h>
struct JointState {
  float angleDeg = NAN;
  float velocityDegPerSec = NAN;
  bool valid = false;
  uint32_t timestampMs = 0;
};
struct FootState {
  float contactLevel = NAN;
  bool valid = false;
  uint32_t timestampMs = 0;
};
struct ImuState {
  float pitchDeg = NAN;
  float rollDeg = NAN;
  float yawDeg = NAN;
  bool valid = false;
  uint32_t timestampMs = 0;
};
class IJointSensor {
public:
  virtual ~IJointSensor() = default;
  virtual bool begin() = 0;
  virtual JointState read() = 0;
};
class IFootSensor {
public:
  virtual ~IFootSensor() = default;
  virtual bool begin() = 0;
  virtual FootState read() = 0;
};
class IImuSensor {
public:
  virtual ~IImuSensor() = default;
  virtual bool begin() = 0;
  virtual ImuState read() = 0;
};
class IMotorDriver {
public:
  virtual ~IMotorDriver() = default;
  virtual bool begin() = 0;
  virtual void disable() = 0;
  virtual bool commandNormalized(float command) = 0; // -1..1, semantics driver-specific
  virtual bool healthy() const = 0;
};
