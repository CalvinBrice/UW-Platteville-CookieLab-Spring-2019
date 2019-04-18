// I2C Master

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
    delay(200); // This is set rather low so much of it won't be used
  }
}

void command(int slaveNumb) {
  int randNumb = random(1,3);
  Wire.beginTransmission(slaveNumb); // Transmit to device #(slaveNumb [numbered 1-2])
  Wire.write(slaveNumb);
  Serial.print("Transmitting to slave ");
  Serial.print(slaveNumb);
  Serial.print(" | wait = ");
  Serial.println(randNumb);
  Wire.endTransmission(); // Stop transmitting
}
