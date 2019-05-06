void goingToOrigin(){
  while (!digitalRead(capSensorPin)) analogWrite(cartControlPin, BACKWARDD);
  analogWrite(cartControlPin, STOP);
}
