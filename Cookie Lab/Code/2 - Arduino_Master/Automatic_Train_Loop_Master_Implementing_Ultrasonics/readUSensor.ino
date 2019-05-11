bool readUSensor(byte slave, int command, int destination, int sensor) {
  byte destinationArray[] = {0,0};
  destinationArray[0] = (destination >> 8) & 0xFF; // maximum int unsigned value is 256
  destinationArray[1] = destination & 0xFF; // Converts ingredient[i].location to a 2 byte variable array (max value is now 65,536)
  Wire.beginTransmission(slave);
  Wire.write(command);
  Wire.write(sensor);
  Wire.write((destination >> 8) & 0xFF);
  Wire.write(destination & 0xFF);
  Wire.endTransmission(slave);
  Wire.requestFrom(slave, 1);
  while (!Wire.available());
  return  Wire.read();
}

