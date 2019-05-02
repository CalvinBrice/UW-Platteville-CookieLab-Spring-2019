void fetchRecipe() {
  while (!Serial.available());
  int leng = Serial.read();
  while (Serial.available() < leng);
  int buf[leng];
  for (int i = 0; i < leng; i++) buf[i] = Serial.read();
  //  Wire.beginTransmission(8);
  //  Wire.write(leng);
  //  for (int i = 0; i < leng; i++) Wire.write(buf[i]);
  //  Wire.endTransmission();
  for (int i = 0; i < leng; i++) ingredient[i].quantity = buf[i];
}
