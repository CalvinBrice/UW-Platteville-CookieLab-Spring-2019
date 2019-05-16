void giveArmControl() {
  Wire.beginTransmission(ARM);
  Wire.write(false); // Sets ARM's variable 'mainInControl' to false
  Wire.endTransmission();
}

