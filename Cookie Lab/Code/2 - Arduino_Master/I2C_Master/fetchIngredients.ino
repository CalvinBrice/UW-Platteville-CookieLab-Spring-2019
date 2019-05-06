void fetchIngredients() {
  moveTrain(TRAIN_SLAVE, GO_TO_ORIGIN); // Tell slave 2 to go to starting position
  bool readyForIng = false; // A temporary variable to keep track of train movement
  bool doneDispensing = false; // A temporary variable to keep track of dispensing
  ingredient[0].trackDirection = bool tempDirection;
  for (int i = 0; i < NUMBER_OF_BAYS; i++) {
    if (ingredient[i].trackDirection != tempDirection) { // Checks to see if train is on the correct track
      Wire.requestFrom(TRAIN_SLAVE, 1); // Requesting a single byte from the train slave
      while (!Wire.available);
      bool atOrigin = Wire.read(); // Byte is from the capacitance sensor
      if (atOrigin) moveTrain(TRAIN_SLAVE, SWITCH_TRACK, 0, ingredient[i].trackDirection); // Tell slave 2 to switch the track to the straight track
      else {
        moveTrain(TRAIN_SLAVE, GO_TO_ORIGIN); // Moves the train back to the origin (i.e. capacitance sensor)
        moveTrain(TRAIN_SLAVE, SWITCH_TRACK, 0, ingredient[i].trackDirection);
      }
      tempDirection = ingredient[i].trackDirection; // Updates tempDirection
    }
    if (ingredient[i].quantity != 0) {
      moveTrain(TRAIN_SLAVE, MOVE, ingredient[i].location, ingredient[i].trackDirection); // Tell slave 2 to move forward to next ingredient at <distance[i]> relative to ultrasonic sensor
      Wire.beginTransmission(TRAIN_SLAVE);
      Wire.write(); // Analog sensor 1, Analog sensor 2, cap sensor <<<<<<<<<<<<<<<<<<<<<<<<<<
      Wire.endTransmission(TRAIN_SLAVE);
      Wire.requestFrom(TRAIN_SLAVE, 1, false); // Requesting a single byte from the train slave
      while (!Wire.available());
      while (Wire.available && !readyForIng){
        readyForIng = Wire.read();
        delay(1);
      }
      Wire.stop();
      dispenseIngredients(DISPENSER_SLAVE, i, ingredient[i].quantity); // Dispense ingredient
      Wire.beginTransmission(TRAIN_SLAVE);
      Wire.write(); // Analog sensor 1, Analog sensor 2, cap sensor <<<<<<<<<<<<<<<<<<<<<<<<<<
      Wire.endTransmission(TRAIN_SLAVE);
      Wire.requestFrom(TRAIN_SLAVE, 1, false); // Requesting a single byte from the train slave
      while (!Wire.available());
      while (Wire.available && !doneDispensing) {
        doneDispensing = Wire.read(); // Train and dispenser are ready to proceed to the next applicable ingredient
        readyForIng = Wire.read();
        delay(1);
      }
      Wire.stop();
    }
  }
}
