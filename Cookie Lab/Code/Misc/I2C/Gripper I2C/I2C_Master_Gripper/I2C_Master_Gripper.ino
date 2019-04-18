// I2C Master Gripper

#include <Wire.h> // Include the required Wire library for I2C
int x = 1;

void setup() {
  Wire.begin(); // Start the I2C Bus as Master
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  for (int i = 1; i < 3; i++) {
    command(i);
    delay(5000); // This is set rather low so much of it won't be used
  }
}

void command(int slaveNumb) {
  Wire.beginTransmission(1); //(slaveNumb); // Transmit to device #(slaveNumb [numbered 1-2])
  Wire.write(slaveNumb);
  Serial.print("Transmitting to slave ");
  Serial.print(1);
  Serial.print(" | wait = ");
  Serial.println(slaveNumb);
  Wire.endTransmission(); // Stop transmitting
}
