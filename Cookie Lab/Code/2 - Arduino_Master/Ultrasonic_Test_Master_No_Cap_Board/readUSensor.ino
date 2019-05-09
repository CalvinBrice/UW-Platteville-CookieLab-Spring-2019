bool readUSensor(byte slave, int sendVariable, byte destination[], int sensor) {
  Wire.beginTransmission(slave);
  Wire.write(sendVariable);
  Wire.write(sensor);
  Wire.write(destination, 2);
  Wire.endTransmission(slave);
  Wire.requestFrom(slave, 1);
  while (!Wire.available());
  return  Wire.read();
}
