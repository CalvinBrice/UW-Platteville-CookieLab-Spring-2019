bool serialWait() {
  while(!Serial.available())
  while(Serial.available()>0)  Serial.read();
  return true;
}

