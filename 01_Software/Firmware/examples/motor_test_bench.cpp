/* WPI exoskeleton: motor communication bench scaffold.
   NO MOTOR OUTPUTS. Replace transport only after exact motor/drive,
   datasheet, wiring, limits, E-stop and safe bench procedure are verified.
   Do not attach to a person. */
#include <Arduino.h>

constexpr uint8_t JOINT_COUNT = 4;
enum Joint : uint8_t { LEFT_HIP, LEFT_KNEE, RIGHT_HIP, RIGHT_KNEE };
const char *jointName[JOINT_COUNT] = {"left_hip", "left_knee", "right_hip", "right_knee"};

struct MotorConfig {
  float gearboxRatio;       // simulation placeholder only
  float continuousTorqueNm; // 0 = unverified
  float peakTorqueNm;       // 0 = unverified
  bool verified;
};
MotorConfig motors[JOINT_COUNT] = {
  {25.0f, 0.0f, 0.0f, false}, {25.0f, 0.0f, 0.0f, false},
  {25.0f, 0.0f, 0.0f, false}, {25.0f, 0.0f, 0.0f, false}
};

// Intentionally absent: CAN frames, PWM output, motor enable and drive commands.
// IDX integrated-drive and EC90 + external driver need different transport layers.
void printInventory() {
  Serial.println("BENCH INVENTORY: output disabled");
  for (uint8_t j = 0; j < JOINT_COUNT; ++j) {
    Serial.print(jointName[j]); Serial.print(" ratio_placeholder=");
    Serial.print(motors[j].gearboxRatio);
    Serial.print(" verified="); Serial.println(motors[j].verified ? "yes" : "no");
  }
}
void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 2000) {}
  Serial.println("MOTOR TEST SCAFFOLD: no motor actuation is implemented.");
  Serial.println("Send 'i' for configuration, 's' for simulated status.");
  printInventory();
}
void loop() {
  if (!Serial.available()) return;
  char c = Serial.read();
  if (c == 'i') printInventory();
  else if (c == 's') Serial.println("Drive status: NOT CONNECTED; no commands sent");
  else Serial.println("Unknown command. Actuation commands are deliberately unavailable.");
}