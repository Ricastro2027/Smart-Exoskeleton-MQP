#pragma once
#include <Arduino.h>
class SampleTimer {
 public:
  explicit SampleTimer(uint32_t periodMs): periodMs_(periodMs) {}
  bool due(uint32_t now) {
    if (uint32_t(now - lastMs_) < periodMs_) return false;
    lastMs_ = now;
    return true;
  }
 private:
  uint32_t periodMs_;
  uint32_t lastMs_ = 0;
};
