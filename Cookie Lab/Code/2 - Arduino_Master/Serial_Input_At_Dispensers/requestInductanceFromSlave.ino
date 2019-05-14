bool requestInductanceFromSlave() {
  Wire.beginTransmission(CART);
  Wire.write(INDUCTOR_CONTROL);
  Wire.endTransmission(CART);
  
  Wire.requestFrom(CART, 1);
  while (!Wire.available()); // Should be stuck here until the capacitance sensor is triggered
  return Wire.read();
}

