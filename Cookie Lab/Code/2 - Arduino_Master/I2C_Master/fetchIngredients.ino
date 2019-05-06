void fetchIngredients() {
  digitalWrite(LED_BUILTIN, HIGH);
  moveTrain(TRAIN, GO_TO_ORIGIN); // Tell slave 2 to go to starting position
  bool tempDirection = ingredient[0].trackDirection; // Initializes tempDirection to the tracks current direction
  for (int i = 0; i < NUMBER_OF_BAYS; i++) {
    if (ingredient[i].trackDirection != tempDirection) { // Checks to see if train is on the correct track
      moveTrain(TRAIN, GO_TO_ORIGIN); // Send train to origin before switching the track
      requestInfoFromSlave(TRAIN, sensor = CAP_SENSOR); // Checks to see if train is at the origin
      moveTrain(TRAIN, SWITCH_TRACK, 0, ingredient[i].trackDirection); // Tell train slave to switch the track direction
      tempDirection = ingredient[i].trackDirection; // Updates tempDirection
    }
    if (ingredient[i].quantity != 0) {
      moveTrain(TRAIN, MOVE, ingredient[i].location, ingredient[i].trackDirection); // Tell slave 2 to move forward to next ingredient at <distance[i]> relative to ultrasonic sensor
      if (ingredient[i].trackDirection) (sensor = ULTRASONIC1);
      else if (!ingredient[i].trackDirection) (sensor = ULTRASONIC2);
      else Serial.println("Error selecting ultrasonic sensor");
      requestInfoFromSlave(TRAIN, sensor);
      dispenseIngredients(DISPENSER, i, ingredient[i].quantity); // Dispense ingredient
      requestInfoFromSlave(DISPENSER);
    }
  }
}
