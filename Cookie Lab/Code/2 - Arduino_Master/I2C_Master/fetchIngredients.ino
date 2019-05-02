void fetchIngredients() {
  moveTrain(TRAIN_SLAVE, GO_TO_ORIGIN); // Tell slave 2 to go to starting position
  for (int i = 0; i < NUMBER_OF_BAYS; i++) {
    if (ingredient[i].quantity != 0) {
      if (ingredient[i].trackDirection) {
        moveTrain(TRAIN_SLAVE, SWITCH_TRACK, 0, ingredient[i].trackDirection);   // Tell slave 2 to switch the track to the straight track
        delay(1000); // Wait for track to switch
        moveTrain(TRAIN_SLAVE, MOVE, ingredient[i].location, ingredient[i].trackDirection); // Tell slave 2 to move forward to next ingredient at <distance[i]> relative to ultrasonic sensor
        Wire.requestFrom(TRAIN_SLAVE, TRAIN_SLAVE); // At location? (TRAIN_SLAVE was replaced by 1, but I'm not sure why
        delay(500);
        while (!Wire.available()) delay(500);
        while (!Wire.read()) delay(500);
        dispenseIngredients(DISPENSER_SLAVE, i, ingredient[i].quantity); // Dispense ingredient
      }
      else if (!ingredient[i].trackDirection) {
        moveTrain(TRAIN_SLAVE, SWITCH_TRACK, 0, ingredient[i].trackDirection); // Tell slave 2 to switch the track to the curved track
        delay(1000);
        moveTrain(TRAIN_SLAVE, MOVE, ingredient[i].location, ingredient[i].trackDirection);
        Wire.requestFrom(TRAIN_SLAVE, 1); // At location?
        while (!Wire.available())
          while (!Wire.read())
            delay(1000);
        dispenseIngredients(DISPENSER_SLAVE, i, ingredient[i].quantity); // Dispense ingredient
      }
      else Serial.println("Error with 'STRAIGHT_TRACK[i]' in fetchIngredients, i = "+String(i));
      delay(1000);
    }
  }
}
