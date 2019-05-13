void giveArmControl() {
  Wire.beginTransmission(ARM);
  Wire.write(true);
  Wire.endTransmission();
}

