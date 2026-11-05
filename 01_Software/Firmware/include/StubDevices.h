#pragma once
#include "Interfaces.h"
// Explicitly unimplemented placeholders: no motor pin is driven.
class StubMotorDriver final : public IMotorDriver {
public:
  bool begin() override { enabled_ = false; return false; }
  void disable() override { enabled_ = false; }
  bool commandNormalized(float) override { return false; }
  bool healthy() const override { return false; }
private:
  bool enabled_ = false;
};
class StubImuSensor final : public IImuSensor {
public:
  bool begin() override { return false; }
  ImuState read() override { return {}; }
};
class StubFootSensor final : public IFootSensor {
public:
  bool begin() override { return false; }
  FootState read() override { return {}; }
};
class StubJointSensor final : public IJointSensor {
public:
  bool begin() override { return false; }
  JointState read() override { return {}; }
};
