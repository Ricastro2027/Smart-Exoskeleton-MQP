# Personalized Gait Detection and Adjustable Assistance

**Status:** Proposed design, not implemented or validated  
**Updated:** 2026-10-29  
**Project:** Lower-limb assistive exoskeleton MQP

## Objective
Develop two linked but independently testable functions:
1. **Personalized gait detection:** identify gait events and stance/swing transitions despite differences in user weight, shoes, gait speed, and FSR mounting.
2. **Adjustable motor assistance:** offer selectable low/medium/high assistance based on gait phase and joint feedback, with conservative safety limits.

Gait detection does **not** by itself establish the amount of assistance a person needs.

## Proposed sensor inputs
- Two foot FSRs per foot: heel and forefoot (four total).
- Four joint potentiometers: left/right hip and knee joint position.
- Four limb-mounted IMUs: one per thigh and shank. Optional pelvis IMU remains under consideration.
- Possible knee-interface pressure sensors are a separate exploratory concept and are **not required** for the initial foot-FSR gait estimator.

The forefoot FSR is intended to be adjustable within the footplate to align with the ball of the shoe. Its carriage/locking mechanism and pressure-transfer pad require mechanical design and validation.

## Electrical interpretation
FSR resistance generally **decreases** with increasing applied force. With the FSR on the 3.3 V side of a voltage divider and a fixed resistor to ground, higher force typically produces a higher ADC reading. The Teensy 4.1 ADC input must remain within its 3.3 V input range. FSR response is nonlinear and affected by mounting, temperature, drift, and loading history.

## Per-user calibration workflow
Perform separately for left heel, left forefoot, right heel, and right forefoot.

1. **Unloaded reference:** record multiple samples with the foot off the ground and no significant pressure on the sensor; average or robustly estimate baseline.
2. **Standing reference:** record samples during supported, comfortable standing. Record both feet independently. Do not require unsupported standing from users unable to do so.
3. **Walking trials:** record several supervised steps at relevant speeds, initially with no powered assistance, to assess sensor peaks, transition order, and usable thresholds.
4. **Quality checks:** reject or flag calibration if standing and unloaded readings are too close, noisy, saturated, or inconsistent; offer recalibration after footwear or sensor-position changes.

### Normalization
For a sensor with readings increasing under load:

```text
loading_ratio = (adc_current - adc_unloaded) /
                (adc_standing - adc_unloaded)
normalized_display = clamp(loading_ratio, 0.0, 1.0)
```

Use only when the denominator is reliably positive and sufficiently above noise. Keep the **unclamped** ratio internally so readings greater than the standing baseline are not lost. A normalized value of 0.5 is **not** necessarily 50% of force; 1.0 represents that sensor's standing reference, **not** maximum force or full body weight.

For gait events, unloaded-based thresholds and walking-derived thresholds may work better than a standing-based ratio alone.

## Gait-state estimation
Initial simplified logic for each foot:

| Heel | Forefoot | Candidate state |
|---|---|---|
| Loaded | Unloaded | Initial heel contact |
| Loaded | Loaded | Stance |
| Unloaded | Loaded | Heel rise / push-off |
| Unloaded | Unloaded | Swing |

These are **candidate** interpretations. A foot with both sensors unloaded could also be lifted while stationary; a foot with both loaded may be standing rather than walking. Use event sequence, time history, IMU angular motion, and joint angle changes to resolve ambiguity.

Proposed implementation:
- Filter ADC signals, preserving gait-transition timing.
- Use separate ON and OFF thresholds (hysteresis) and minimum persistence to suppress noise.
- Implement a finite-state machine with plausible transitions, rather than relying on a single instantaneous threshold.
- Log raw ADC, normalized readings, IMU data, joint angles, detected states, and timestamps for analysis.
- Validate against annotated video or another independent gait reference.

## Adjustable assistance (future motor integration)
Offer configurable **low / medium / high** assistance profiles. These must **not** simply map to arbitrary percentages of motor voltage. Once the motors, drivers, transmissions, and feedback are chosen, define measurable control targets (e.g., bounded joint torque/current or carefully validated motion assistance), and enforce joint-position, velocity, current/torque, and fault limits.

Suggested software pipeline:

```text
FSRs + IMUs + joint potentiometers
    -> sensor acquisition and filtering
    -> user calibration and quality checks
    -> gait-state estimator
    -> assistance policy (user-selected profile)
    -> joint controller and independent safety checks
    -> motor drivers
```

**Mechanical dependency:** a non-backdrivable worm transmission could prevent user-initiated motion from appearing in joint-angle measurements. FSRs and IMUs alone cannot directly measure intended joint torque. Before implementing assist-as-needed control, verify backdrivability and determine whether an interaction-force or joint-torque sensing method is needed.

## Development and validation milestones
- [ ] Acquire and bench-test foot FSRs and voltage dividers on Teensy 4.1.
- [ ] Confirm pressure-pad geometry, embedded mount, wiring protection, and sensor-carrier lock.
- [ ] Collect unloaded and standing baselines for four sensors.
- [ ] Implement normalization with invalid-calibration detection.
- [ ] Log gait trials and inspect heel-to-forefoot loading transitions.
- [ ] Implement and validate an FSR/IMU gait-state machine.
- [ ] Define motor control interface after motor/gearbox selection.
- [ ] Verify electrical and mechanical safety on a bench setup before powered wearable testing.
- [ ] Evaluate low/medium/high assistance in a supervised, approved testing protocol.

## Open questions
1. Final FSR model/range and pressure-pad dimensions?
2. Best contact thresholds across shoe sizes and user loading patterns?
3. Does the footplate mount allow reliable FSR placement without uncomfortable pressure concentration?
4. Are the chosen transmissions sufficiently backdrivable for voluntary initiation?
5. What additional force/torque feedback is needed to provide safe, meaningful assistance?
6. What measurable outcomes will establish gait-classification accuracy and assistance benefit?

> **Documentation note:** All thresholds, calibration methods, and assistance strategies above are initial engineering proposals. No gait-classification accuracy, safety performance, or clinical benefit is claimed without testing.
