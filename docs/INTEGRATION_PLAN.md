# Integration roadmap (placeholders, not implemented hardware support)

## Devices
- Joint potentiometers: use existing raw analog helpers; calibrate each physical joint.
- IMUs: replace `StubImuSensor` with a driver for the chosen model and bus.
- FSRs: replace `StubFootSensor` with calibrated pressure/contact sensing.
- EMG (optional): define signal conditioning and sampling only after hardware choice.
- Motors: replace `StubMotorDriver` with the exact driver interface and documented disable/fault behavior.
- Power and protection: verify independent physical power cutoff, fusing and driver current limiting.
- Optional battery monitor: read voltage/current from an appropriately isolated interface.

## Pipeline
Read sensors -> validate timestamps and ranges -> estimate joint/gait state ->
check safety state -> compute limited assistance request -> motor driver.

## Control work to be implemented
- Explicit operating states and fault latching, never automatic re-enable
- Hardware enable and independent cutoff feedback
- Position/velocity/current constraints and motion ramping
- Sensor disconnect, bus failure and watchdog response
- Test fixtures and logs for each joint and full system

`examples/system_skeleton.cpp` demonstrates API composition only. It intentionally cannot enable motor output. No gait algorithm or motor control law has been validated.
