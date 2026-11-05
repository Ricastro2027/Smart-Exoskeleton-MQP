# MQP Engineering Documentation Index

This repository is the working engineering record for the WPI lower-limb assistive exoskeleton MQP. The final academic report may later be drafted in Word from these records.

## How to use these records
- **Verified:** observed, measured, or supported by an identified artifact.
- **Planned:** intended but not completed.
- **Considering:** option under evaluation.
- **Pending verification:** historical statement or parameter that requires confirmation.
- Never present planned human trials, simulations, unpurchased hardware, or compiled firmware as physical validation.
- Keep sources with bibliographic details and links; never invent citations.
- Record the test date separately from the date the report was written.
- Keep one report per test; include setup, equipment, procedure, raw data, observations, limitations, and next steps.

## Documentation map
- [Project history](progress/PROJECT_HISTORY.md): reconstructed decisions and milestones.
- [Design decision register](design-decisions/DECISION_REGISTER.md): current choices, candidates, and rationale.
- [Research register](research/RESEARCH_REGISTER.md): literature and source tracking.
- [Existing test record](tests/2026-10-28_potentiometer_resistance_test.md): four 10 kΩ potentiometers, basic resistance response.
- [Existing test template](TEST_LOG_TEMPLATE.md): future test reports.
- [Existing architecture](ARCHITECTURE.md), [integration plan](INTEGRATION_PLAN.md), [safety plan](SAFETY_PLAN.md), and [wiring diagram](WIRING_DIAGRAM.md).

## Suggested reporting cadence
At each meaningful change, record: date, activity, evidence, decision, unresolved questions, and next action. Use GitHub commit history for traceability, not as a substitute for engineering test records.

## Safety boundary
Firmware compilation is not hardware validation. Motor output is currently disabled. Powered wearable testing requires independent safety hardware, hazard analysis, supervised validation, and appropriate institutional approval.
