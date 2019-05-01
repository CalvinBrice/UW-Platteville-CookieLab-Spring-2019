void fetchRecipe() {
  while (!Serial.available());
  leng = Serial.read();
  while (Serial.available() < leng) digitalWrite(ledPin, HIGH);
  digitalWrite(ledPin, LOW);
  int buf[leng];
  for (int i = 0; i < leng; i++) buf[i] = Serial.read();
  Wire.beginTransmission(8);
  Wire.write(leng);
  for (int i = 0; i < leng; i++) Wire.write(buf[i]);
  Wire.endTransmission();
}
