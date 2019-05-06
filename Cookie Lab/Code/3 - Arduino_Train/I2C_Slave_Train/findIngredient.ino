void findIngredient(int destination, int sensor) {
  isTrainAtLocation = false;
  switch (sensor) {
    case ULTRASONIC1:
      ultrasonicValue2 = analogRead(ultrasonicRead2);
      while (destination < ultrasonicValue1 || destination > ultrasonicValue1) {
        if (destination > ultrasonicValue1) analogWrite(cartControlPin, FOWARDD);
        else if (destination < ultrasonicValue1) analogWrite(cartControlPin, BACKWARDD);
        ultrasonicValue2 = analogRead(ultrasonicRead2);
      }
      break;
    case ULTRASONIC2:
      ultrasonicValue2 = analogRead(ultrasonicRead2);
      while (destination < ultrasonicValue2 || destination > ultrasonicValue2) {
        if (destination > ultrasonicValue2) analogWrite(cartControlPin, FORWARDD);
        else if (destination < ultrasonicValue2) analogWrite(cartControlPin, BACKWARDD);
        ultrasonicValue2 = analogRead(ultrasonicRead2);
      }
      break;
    default:
      Serial.println("Error selecting sensor");
      break;
  }
  analogWrite(cartControlPin, STOP);
  findIngredient(destination, sensor); // Confirming train is at destination

  isTrainAtLocation = true;
  command = DO_NOTHING;
}
