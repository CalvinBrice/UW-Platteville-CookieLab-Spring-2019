void sendCommand(byte slave, int command){
  Wire.beginTransmission(slave);
  Wire.write(CART_CONTROL);
  Wire.write(command);
  Wire.endTransmission(slave);
  Serial.println(command);
}
