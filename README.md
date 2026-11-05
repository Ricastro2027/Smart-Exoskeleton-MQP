# Smart Exoskeleton MQP | Software & Sensors

This repository contains the WPI lower-limb exoskeleton's Teensy firmware, sensor development notes, electrical integration information, and test history. The team's overall project files and CAD remain in its shared Outlook folder.

## Start here

| Folder | What to find there |
| --- | --- |
| [01_Software](01_Software/) | Teensy 4.1 firmware, PlatformIO settings, example programs, architecture, control and integration notes |
| [02_Sensors](02_Sensors/) | Sensor specifications, selection research, calibration and placement notes |
| [03_Electrical](03_Electrical/) | Wiring, pin assignments, hardware checklist and electrical safety |
| [04_Testing](04_Testing/) | Physical test records, results, failed experiments and test-log template |

## Running firmware

1. Install VS Code with the PlatformIO extension.
2. Open **[01_Software/Firmware](01_Software/Firmware/)** as the PlatformIO project folder (not the repository root).
3. Select the environment from [platformio.ini](01_Software/Firmware/platformio.ini) and build.
4. Serial monitor speed: **115200 baud**.

The PlatformIO folders are conventional: `src/` is the primary program, `include/` holds reusable C++ headers, and `examples/` contains separately selectable bench programs. Do not move these folders individually without updating the build configuration.

**Current status:** Firmware is in development. Some code is incomplete and may not compile. Compilation alone is not hardware validation. Motor control and wearable testing require independent safeguards and supervised verification.

## Keeping a useful engineering history

Record successful **and unsuccessful** tests. Each record should include date, equipment, procedure, measured data, observations, limitations, and next steps. Mark untested ideas as *proposed*, not *verified*. Use [the test-log template](04_Testing/TEST_LOG_TEMPLATE.md).

Older design notes and project history are retained in [Software documentation](01_Software/Documentation/), rather than deleted. Some links inside those historical documents may still use their original paths.
