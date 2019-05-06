void findIngredient(int destination, int sensor) {
  isTrainAtLocation = false;
  switch (sensor) {
    case ULTRASONIC1:
      ultrasonicValue2 = analogRead(ultrasonicRead2);
      while (destination < ultrasonicValue1 || destination > ultrasonicValue1) {
        if (destination > ultrasonicValue1) digitalPotWrite(FORWARDD);
        else if (destination < ultrasonicValue1) digitalPotWrite(BACKWARDD);
        ultrasonicValue2 = analogRead(ultrasonicRead2);
      }
      break;
    case ULTRASONIC2:
      ultrasonicValue2 = analogRead(ultrasonicRead2);
      while (destination < ultrasonicValue2 || destination > ultrasonicValue2) {
        if (destination > ultrasonicValue2) digitalPotWrite(FORWARDD);
        else if (destination < ultrasonicValue2) digitalPotWrite(BACKWARDD);
        ultrasonicValue2 = analogRead(ultrasonicRead2);
      }
      break;
    default:
      Serial.println("Error selecting sensor");
      break;
  }
  digitalPotWrite(STOP);
  findIngredient(destination, sensor); // Confirming train is at destination

  isTrainAtLocation = true;
  command = DO_NOTHING;
}
