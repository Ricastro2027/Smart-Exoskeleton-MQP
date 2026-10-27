# October 26 design decisions and integration status

Recovered source sketches are now under `examples/` as PlatformIO `.cpp` test environments:
- `sensor_testing`: full sensor-only preflight and monitoring prototype.
- `full_exoskeleton_dry_run`: integration dry run, no motor actuation.
- `motor_test_bench`: motor inventory and communications scaffold, no motor outputs.

## Preflight
BOOT -> WAIT_CALIBRATION -> CALIBRATING (3 seconds stationary thigh baseline) -> MONITORING, or latched FAULT.
- Four MPU6050 IMUs through TCA9548A channels 0-3; physical Teensy pins 18/19 are I2C.
- Four potentiometers on A7-A10; four foot FSRs on A1/A2/A3/A11.
- Two thigh cuff FSRs on A12/A6; START active-low on pin 6.
- Mode inputs HIGH/MEDIUM/ECO on 3/4/5 are display-only.
- Buzzer pin 7 reserved for compatible driver; original fault logic keeps buzzer LOW.
- Nominal 200 Hz (5 ms) sampling and 100 ms telemetry. Timing is not guaranteed; validate actual IMU bus throughput.
- 10 consecutive scheduler overruns trigger a latched fault in sensor prototype.
- Baseline reflects cuff pressure changes, **not** EMG or validated movement intent.

## Not verified or enabled
- Foot-contact thresholds, joint angle calibration and 25:1 example reduction.
- Battery voltage monitoring and protection.
- Motor electrical interface, commands, safety cutoff, or motion enable.
- Physical hardware tests and build success.

## Important
`src/main.cpp` is a passive raw-input monitor. Select `sensor_testing` or `full_exoskeleton_dry_run` explicitly to run the recovered preflight. Old examples now use the shared pin mapping from the previous discussion; check wiring before flashing.

No sketch is approved for human-worn testing.
