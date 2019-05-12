bool doneDispensing(int bay, int quantity) {
  Serial.println("Bay "+String(bay));
  Wire.beginTransmission(DISPENSER);
  Wire.write(bay);
  Wire.write(quantity);
  Wire.endTransmission(DISPENSER);
  
  Wire.requestFrom(DISPENSER, 1);
  while (!Wire.available());
  return  Wire.read();
}

