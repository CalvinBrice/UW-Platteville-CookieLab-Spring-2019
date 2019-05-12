bool requestCapacitanceFromSlave() {
  Wire.beginTransmission(CART);
  Wire.write(CAP_CONTROL);
  Wire.endTransmission(CART);
  
  Wire.requestFrom(CART, 1);
  while (!Wire.available()); // Should be stuck here until the capacitance sensor is triggered
  return Wire.read();
}

