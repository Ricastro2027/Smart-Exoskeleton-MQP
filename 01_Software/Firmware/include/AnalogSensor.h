#pragma once
#include <Arduino.h>
class AnalogSensor {
 public:
  explicit AnalogSensor(uint8_t pin): pin_(pin) {}
  void begin() const { pinMode(pin_, INPUT); }
  uint16_t readRaw() const { return analogRead(pin_); }
  static float normalized(uint16_t raw) { return constrain(raw / 4095.0f, 0.0f, 1.0f); }
 private:
  uint8_t pin_;
};
