void instruct(int slave, byte command, byte variable = 0, byte straight = true) { // Variable is a distance/direction/step count/ depending on the slaveNumb and command
  Wire.beginTransmission(slave); // Transmit to device #(slaveNumb [numbered 1-4])
  Wire.write(command);
  Wire.write(variable);
  Wire.write(straight);
  //  Serial.print(slave);
  //  Serial.print("  ");
  Serial.print(command);
  Serial.print("  ");
  Serial.print(variable);
  Serial.print("  ");
  Serial.println(straight);
  Wire.endTransmission(); // Stop transmitting
}
