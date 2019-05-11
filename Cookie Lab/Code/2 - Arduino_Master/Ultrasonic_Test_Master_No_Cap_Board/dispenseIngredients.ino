bool dispenseIngredients(byte slave, int bay, int quantity, int mode) {
  //  Serial.println("Bay: " + String(bay+1) + " | Quantity: " + String(quantity)+ " | Mode: " + String(mode));
  Wire.beginTransmission(slave); // Transmit to device #(slaveNumb [numbered 0x08-0x12])
  Wire.write(bay);
  Wire.write(quantity);
  Wire.write(mode);
  Wire.endTransmission(); // Stop transmitting
  Wire.requestFrom(slave, 1);
  while (!Wire.available());
  return  Wire.read();
}

