void switchTrack(byte slave, bool straightTrack) {
  Wire.beginTransmission(slave); // Transmit to device #(slaveNumb [numbered 1-4])
  Wire.write(straightTrack);
  Wire.endTransmission(); // Stop transmitting
}

