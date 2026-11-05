# Exoskeleton safety plan (draft, not a certification)
## Current status
Sensor-only prototype. No motor output or human-use authorization.
## Required independent hardware safety
- Select a latching, normally closed emergency-stop device. The existing small momentary button is START, not an E-stop.
- Select a safety circuit compatible with the final motor drivers, power architecture, and their verified torque-disable inputs. Teensy GPIO must not be the sole stop mechanism.
- Ensure E-stop actuation remains effective if firmware freezes, power is interrupted, or a wire breaks. Evaluate a safety-rated architecture with the advisor.
- Determine what happens mechanically when torque disappears: gravity, backdrivability, gear lock-up, wearer support, and joint travel. Emergency stopping must not create a fall or crush hazard.
- Releasing/resetting E-stop must not cause motion. Require a separate deliberate re-enable procedure.
- Define hard joint limits, power/current limits, thermal monitoring, watchdogs, and fault handling before powered testing.
## Software layer
SafetyManager latches fault reports. Its motorPermission() always returns false in the present prototype. The E-stop GPIO pin is **not assigned** until the circuit and wiring are designed. No motor driver commands are implemented.
## Validation gates
1. Advisor reviews hazard analysis and wiring.
2. Bench-test E-stop independently of firmware, including a simulated Teensy hang and disconnected control wire.
3. Validate torque-off behavior and mechanical support without a wearer.
4. Validate all sensor and timing fault responses, motor-driver faults, and no-auto-restart.
5. Obtain required institutional approvals before any human testing.
