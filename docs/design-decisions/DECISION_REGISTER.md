# Engineering Decision Register

**Updated:** 2026-10-28. Statuses reflect discussions, not formal team approval unless noted.

| Topic | Current direction | Status | Rationale / follow-up |
| --- | --- | --- | --- |
| Central controller | Teensy 4.1 | Working firmware target | Arduino-compatible; validate hardware pinout and timing |
| Hip and knee sensing | Four 10 kΩ linear potentiometers | Components tested for basic resistance response | Voltage and joint-angle calibration pending |
| IMUs | Four MPU6050 with TCA9548A mux | Proposed | Validate addressing, mounting, timing, and interference |
| Ground-contact sensing | Foot and thigh FSRs | Proposed | Verify quantity, placement, thresholds and repeatability |
| Muscle-intent sensing | EMG | Under consideration | Signal quality and control complexity unresolved |
| Motors | Maxon EC90 Flat candidates | Under consideration | Sponsorship, driver, torque/speed and thermal sizing unresolved |
| Transmission | Worm/planetary/belt concepts | Under consideration | Select using torque, efficiency, size, backdrivability and safety analysis |
| Ankle | Passive spring mechanism | Planned | Mechanical design and testing pending |
| Wireless telemetry | ESP32 to laptop, likely Wi-Fi | Desired / proposed | Monitoring only; local control must not depend on radio |
| Data logging | USB during development, possible onboard SD | Proposed | Define data format, rates and synchronization |
| Safety | Independent hardware stop and safe torque disable | Required before actuation | Current firmware fail-closed logic is not a physical E-stop |
| Budget | $250/student, $1,500 total | Current reported allocation | Track actual purchases and sponsor commitments |

## Decision record template
For each finalized decision, capture: date, decision owner(s), alternatives, evidence/sources, tradeoffs, safety implications, cost, verification plan, and revision history.
