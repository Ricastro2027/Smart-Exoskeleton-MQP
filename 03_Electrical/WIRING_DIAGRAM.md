# Provisional Teensy 4.1 wiring reference
**Not a validated wiring diagram. Verify pin labels, 3.3 V levels, grounds, sensor conditioning, and wiring before connection.**
| Function | Teensy pin | Status |
|---|---|---|
| START momentary button (active low) | D6 | Existing |
| Mode HIGH / MEDIUM / ECO | D3 / D4 / D5 | Provisional |
| Buzzer output | D7 | External compatible driver required |
| Left heel / forefoot FSR | A1 / A2 | Provisional |
| Right heel / forefoot FSR | A3 / A11 | Provisional |
| Left / right thigh FSR | A12 / A6 | Provisional |
| Left hip / knee potentiometer | A7 / A8 | Provisional |
| Right hip / knee potentiometer | A9 / A10 | Provisional |
| I2C SDA / SCL | D18 / D19 | Teensy Wire bus |
| TCA9548A multiplexer | I2C address 0x70 | Four MPU6050s on channels 0-3 |
| Optional battery voltage sense | A0 | **Do not connect** until a safe divider/protection is designed |
| Hardware E-stop / safety status | **TBD** | Independent safety circuit required |
| Motor driver connections | **TBD** | No drivers selected or enabled |
All analog inputs must be within the Teensy 4.1's allowed voltage range (0–3.3 V). FSRs require an appropriate measurement circuit. The current small button is START, not the E-stop.
