# Potentiometer resistance test

**Date recorded:** 2026-10-28 (test date not independently confirmed)
**Project:** Smart Exoskeleton MQP
**Component:** Adafruit panel-mount 10 kΩ linear potentiometer, Product ID 562
**Quantity:** Four
**Equipment:** Digital multimeter, 20 kΩ resistance range

## Procedure

Each potentiometer was tested individually with a multimeter while manually rotating the shaft. The user reported observing a resistance change from approximately 0 kΩ to 9–10 kΩ on all four units.

## Observations

| Unit | Reported resistance range | Behavior | Initial result |
| --- | --- | --- | --- |
| 1 | ~0–9/10 kΩ | Similar to other units | Basic response verified |
| 2 | ~0–9/10 kΩ | Similar to other units | Basic response verified |
| 3 | ~0–9/10 kΩ | Similar to other units | Basic response verified |
| 4 | ~0–9/10 kΩ | Similar to other units | Basic response verified |

Exact readings, terminal selection, and rotation angle were not recorded. The reported observations support basic functionality, but do not independently establish linearity, smoothness under high-resolution sampling, electrical end stops, or reliability.

## Pending validation

- Verify resistance between the two outer terminals against nominal 10 kΩ and tolerance.
- Check for intermittent readings across the full usable rotation.
- Apply a regulated 3.3 V across the outer terminals and measure wiper output (power disconnected before any resistance measurement).
- Record mechanical rotation and installed zero angle for each joint.
- Verify Teensy 4.1 analog readings and calibrate each sensor after installation.

**Firmware changes:** None required by this initial resistance test. Motor activation remains disabled pending independent safety validation.
