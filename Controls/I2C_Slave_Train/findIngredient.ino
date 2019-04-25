void findIngredient(int destination, bool straight) {
  isTrainAtLocation = false;
  Serial.println("Finding ingredients");
  int volt_to_cm = 120; // Voltage to centimeter conversion Totally random, fix this <<<<<<<<<<<<<<<<<<
  int ultrasonicSensor;
  Serial.print("Destination: ");
  Serial.println(destination);
  Serial.print("Straight? ");
  Serial.println(straight);
  if (straight) ultrasonicSensor = A0;
  else if (!straight) ultrasonicSensor = A1;

  //  int currentdestination = (5-analogRead(ultrasonicSensor)) * volt_to_cm;
  //  while (currentdestination > destination || currentdestination < destination) {
  //    if (currentdestination > destination) digitalPotWrite(FORWARD);
  //    else if (currentdestination < destination) digitalPotWrite(BACKWARD);
  //    currentdestination = (5-analogRead(ultrasonicSensor)) * volt_to_cm;
  //  }
  for (int i = 0; i < 10; i++) delay(500);
  isTrainAtLocation = true;
  digitalPotWrite(STOP);
}
