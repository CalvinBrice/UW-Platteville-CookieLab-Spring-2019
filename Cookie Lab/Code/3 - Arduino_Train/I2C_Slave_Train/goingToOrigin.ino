void goingToOrigin(){
  while (!digitalRead(CAP_SENSOR)) analogWrite(trainControlPin, BACKWARDD);
  analogWrite(trainControlPin, STOP);
}
