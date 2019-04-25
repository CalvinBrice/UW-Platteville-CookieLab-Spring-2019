void startingLocation(){
  Serial.println("Going to origin");
//  while (!digitalRead(CAP_SENSOR)) digitalPotWrite(BACKWARD);
  digitalPotWrite(STOP);
  Serial.println("Finished going to origin");
}
