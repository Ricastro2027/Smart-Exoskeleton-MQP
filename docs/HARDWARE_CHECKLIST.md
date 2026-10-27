# Hardware bring-up checklist

Do not test the wearable exoskeleton on a person until the mechanical, electrical and controls safety review is complete.

## Before powering the Teensy
- [ ] Confirm Teensy 4.1 pinout and 3.3 V input levels (not 5 V tolerant).
- [ ] Verify all sensor supply voltages and grounds with a multimeter.
- [ ] Verify potentiometer wipers cannot exceed 3.3 V.
- [ ] Confirm wiring against `include/PinConfig.h`.
- [ ] Disconnect all motor power during sensor tests.

## Sensor validation
- [ ] Read each potentiometer through its full safe mechanical travel.
- [ ] Record raw endpoints and measured physical angles for each joint.
- [ ] Repeat readings to evaluate noise, drift and discontinuities.
- [ ] Check disconnected, shorted, and out-of-range input behavior.
- [ ] Test the push button, including release and bounce.
- [ ] Record IMU and FSR model numbers, supply voltages and interfaces before adding drivers.

## Motor bench testing (future)
- [ ] Confirm exact motor and driver models, pinout, command interface and feedback.
- [ ] Verify supply sizing, wiring protection, fusing and current limiting.
- [ ] Implement independent hardware power cutoff and verify it works.
- [ ] Implement disabled-at-startup state, fault latching and watchdog behavior.
- [ ] Check mechanical stops, joint direction, gearbox ratio and encoder polarity.
- [ ] Begin unloaded at minimum current and speed under supervision.
- [ ] Validate hardware cutoff independently of firmware.

A momentary GPIO button is not a safety-rated emergency stop.
