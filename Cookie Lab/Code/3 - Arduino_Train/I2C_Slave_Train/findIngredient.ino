void findIngredient(int destination, int sensor) {
  digitalWrite(cartDirectionPin, HIGH); // Sets cart moving forward
  isTrainAtLocation = false;
  switch (sensor) {
    case ULTRASONIC1:
      ultrasonicValue1 = analogRead(ultrasonicRead1);
      while (destination - 5 < ultrasonicValue1 || destination + 5 > ultrasonicValue1) {
        analogWrite(trackPWM, SLOW);
        if (destination > ultrasonicValue1) digitalWrite(cartDirectionPin, HIGH);
        else if (destination < ultrasonicValue1) digitalWrite(cartDirectionPin, LOW);
        ultrasonicValue1 = analogRead(ultrasonicRead1);
      }
      break;
    case ULTRASONIC2:
      ultrasonicValue2 = analogRead(ultrasonicRead2);
      while (destination - 5 < ultrasonicValue2 || destination + 5 > ultrasonicValue2) {
        analogWrite(trackPWM, SLOW);
        if (destination > ultrasonicValue2) digitalWrite(cartDirectionPin, HIGH);
        else if (destination < ultrasonicValue2) digitalWrite(cartDirectionPin, LOW);
        ultrasonicValue2 = analogRead(ultrasonicRead2);
      }
      break;
    default:
      Serial.println("Error selecting sensor");
      break;
  }
  analogWrite(trackPWM, STOP);
  findIngredient(destination, sensor); // Confirming train is at destination

  isTrainAtLocation = true;
  command = DO_NOTHING;
}
