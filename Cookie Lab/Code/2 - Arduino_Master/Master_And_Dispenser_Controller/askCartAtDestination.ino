 bool askCartAtDestination(byte slave, int sentVariable, int destination, int sensor)  {
  Wire.beginTransmission(slave);
  Wire.write(sentVariable);
  Wire.write(sensor);
  Wire.write(destArray, 2);
  Wire.endTransmission(slave);
  
  Wire.requestFrom(slave,1);
  return Wire.read();
}

