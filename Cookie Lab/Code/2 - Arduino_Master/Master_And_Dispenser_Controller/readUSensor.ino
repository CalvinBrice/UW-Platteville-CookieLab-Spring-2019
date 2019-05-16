bool readUSensor(byte slave, int command, int destination, bool straightSide) {
  int ultrasonic = NO_SENSOR;
  if (straightSide) ultrasonic = U1;
  else if (!straightSide) ultrasonic = U2;
  byte destinationArray[] = {0,0};
  destinationArray[0] = (destination >> 8) & 0xFF; // maximum int unsigned value is 256
  destinationArray[1] = destination & 0xFF; // Converts ingredient[i].location to a 2 byte variable array (max value is now 65,536)
  Wire.beginTransmission(slave);
  Wire.write(command);
  Wire.write(ultrasonic);
  Wire.write(destinationArray, 2);
  Wire.endTransmission(slave);
  
  Wire.requestFrom(slave, 1);
//  while (!Wire.available()); // User 'Koepel' on github noted this as a common mistake where available() is not need following a requestFrom()
  return  Wire.read();
}

