# Firmware architecture

## Current (implemented)
- `include/PinConfig.h`: provisional Teensy pin assignments
- `include/AnalogSensor.h`: reusable raw analog input helper
- `include/JointCalibration.h`: linear raw-to-angle conversion helper
- `include/SensorHealth.h`: preliminary bench-only plausibility and freshness helpers
- `include/SampleTimer.h`: nonblocking periodic sampling
- `examples/`: individually selectable firmware demonstrations
- `src/main.cpp`: passive combined input monitor

## Planned (not implemented)
1. Sensor drivers for selected IMUs, FSRs and optional EMG.
2. Sensor filtering and calibration storage.
3. Motor-driver abstraction for selected driver and motor hardware.
4. Fault-handling state machine with power-off default and independent hardware cutoff.
5. Bench-only closed-loop joint position tests.
6. Multi-joint coordination and gait-assistance algorithms.

The Teensy is not a substitute for independent electrical and mechanical safeguards.
