void startingLocation(){
  while (!digitalRead(CAP_SENSOR)) digitalPotWrite(BACKWARDD);
  digitalPotWrite(STOP);
}
