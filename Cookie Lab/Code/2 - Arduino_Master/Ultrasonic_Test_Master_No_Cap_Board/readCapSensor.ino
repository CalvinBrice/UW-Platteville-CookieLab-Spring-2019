bool readCapSensor(byte slave, int sensor) {
  Wire.beginTransmission(slave); // Transmit to device #(slaveNumb [numbered 1-4])
  Wire.write(CAP_CONTROL);
  Wire.write(sensor);
  Wire.endTransmission(); // Stop transmitting
  Wire.requestFrom(slave, 1);
  while (!Wire.available());
  return  Wire.read();
}

