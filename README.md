# Smart Exoskeleton MQP

Teensy 4.1 Arduino C++ firmware scaffold for the WPI lower-limb exoskeleton.

## Getting started
1. Install VS Code and the PlatformIO IDE extension.
2. Clone this repository, then open its root folder in VS Code.
3. Select a PlatformIO environment and build/upload.
4. Open Serial Monitor at 115200 baud.

## Test environments
- `teensy41`: default, four potentiometers plus button
- `potentiometer`: one potentiometer
- `button`: one momentary button
- `combined_inputs`: potentiometer plus button

CLI example: `pio run -e potentiometer -t upload`.
Monitor: `pio device monitor -b 115200`.

## Hardware notes
Pin assignments in `include/PinConfig.h` are provisional.
- Teensy 4.1 inputs are 3.3 V only, not 5 V tolerant.
- Potentiometer: outer terminals to 3.3 V and GND, wiper to analog pin.
- Two-wire momentary button: pin 2 and GND, using internal pull-up.
- Values are raw ADC counts, not calibrated joint angles.
- The button is **not** a safety-rated emergency stop.

**Motor output is intentionally not implemented.** Confirm motor driver, supply, independent hardware power cutoff, current limits, watchdog, and mechanical joint limits before developing bench motor tests. Do not test the mechanism on a person.

## Next
Add actual IMU/FSR drivers and motor-driver integration after hardware selection. Validate components separately, then combine them with fault handling and safe startup.

## Additional tests
- `analog_health`: raw ADC readings, normalized values and rail warnings.
- `joint_calibration`: demonstration of raw-to-angle conversion. **Replace example endpoints before relying on angles.**

See `docs/HARDWARE_CHECKLIST.md` before connecting hardware, `docs/ARCHITECTURE.md` for planned modules, and `docs/TEST_LOG_TEMPLATE.md` for recording bench results.

A GitHub Actions workflow attempts to compile all firmware environments on pushes and pull requests. Its success must be checked in GitHub Actions; compilation is not proof of hardware safety.
