# Project History and Status

**Compiled:** 2026-10-28. This is a retrospective summary from project discussions and existing repository materials, **not** a contemporaneous laboratory notebook. Dates below identify discussion or documentation periods unless explicitly stated as a test date.

## Project purpose
WPI MQP developing an adjustable lower-limb assistive exoskeleton to support mobility and potentially rehabilitation. Planned powered hip and knee assistance; ankle assistance is passive/spring-based. Human-use suitability and benefits remain research/design goals, not demonstrated outcomes.

## Team and resources
- Six students: four Mechanical Engineering and two Robotics Engineering.
- Workspace in Higgins; possible reuse of parts from an older exoskeleton in the building.
- Current reported allocation: $250 per student, **$1,500 total**; CS/ECE portion capped at $250 with preference to spend less. Older proposal estimates were higher and should not be treated as the current budget.
- Potential Maxon sponsorship/discounts are **not confirmed**.

## Schedule (planning)
- A term: requirements, proposal, research, concept development, CAD, component selection.
- B term: build, manufacturing, integration.
- C term: testing and iterative adjustment.
- Early D term: final testing; late D term: paper and presentation.
Actual progress may differ from this plan.

## Engineering status
- Rough CAD and joint-torque simulation were reported in earlier discussions; underlying models/results should be attached or linked before quoting numerical outcomes.
- Motor candidates discussed: Maxon EC90 Flat 500267/500269. Motor, gearbox, drivers, and transmission are not finalized. Worm gear, planetary reduction, and timing belt concepts have been discussed.
- Power: removable/swappable battery concept under consideration; pack sizing and electrical protections pending.
- Teensy 4.1 selected as current firmware target, not yet physically integrated.
- Four 10 kΩ Adafruit panel-mount linear potentiometers available and manually tested; four IMUs through an I2C multiplexer, foot/thigh FSRs, and possible EMG have been discussed. Confirm physical inventory and final sensor architecture before claiming all are installed.
- Wireless live telemetry to a laptop is desired; ESP32 Wi-Fi/Bluetooth bridge is a **proposal**, not implemented.
- Firmware repository includes sensor-only programs, examples, safety-state scaffolding, and PlatformIO builds. Compilation success does not imply real-world performance.

## October 2026 sensor testing
User reports all four Adafruit 10 kΩ potentiometers were checked with a multimeter on its 20 kΩ range. Rotating each shaft changed resistance from approximately 0 to 9–10 kΩ; all behaved similarly. Exact values, test date, terminal wiring, linearity, and voltage output were not recorded. See linked test report.

## Validation and research boundaries
- Initial resistance response of four potentiometers: **reported completed**.
- Sensor voltage, Teensy acquisition, calibration, installed joint-angle mapping: **pending**.
- Motor actuation and wearable testing: **not validated**.
- Future feedback sessions with WPI Athletics/community: **planned only**, subject to approvals and safety review.
- UMass Memorial collaboration: **aspirational**, not established.

## Next actions
1. Verify the individual potentiometers' 3.3 V output, mechanical ranges, and joint mounting/calibration.
2. Confirm sensor inventory, motor driver interfaces, safety architecture, and actual budget commitments.
3. Capture research sources and advisor/team decisions with dates and citations.
4. Develop and validate wired telemetry before considering optional wireless display.
