bool requestInductanceFromSlave() {
  Wire.beginTransmission(CART);
  Wire.write(INDUCTOR_CONTROL);
  Wire.endTransmission(CART);
  
  Wire.requestFrom(CART, 1);
  return Wire.read(); // Should be stuck here until the capacitance sensor is triggered
}

