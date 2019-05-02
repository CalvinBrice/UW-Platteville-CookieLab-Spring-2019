void moveTrain(int slave, byte command, byte variable = 0, byte straight = true) { // Variable is a distance/direction/step count/ depending on the slaveNumb and command
  Wire.beginTransmission(slave); // Transmit to device #(slaveNumb [numbered 1-4])
  Wire.write(command);
  Wire.write(variable);
  Wire.write(straight);
  Wire.endTransmission(); // Stop transmitting
  Serial.println("Command: " + String(command) + " | Variable: " + String(variable) + " | Straight?: " + String(straight));
}
