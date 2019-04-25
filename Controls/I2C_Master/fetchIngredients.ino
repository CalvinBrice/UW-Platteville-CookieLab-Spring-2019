void fetchIngredients() {
  instruct(TRAIN_SLAVE, GO_TO_ORIGIN); // Tell slave 2 to go to starting position
  for (int i = 0; i < NUMBER_OF_BAYS; i++) {
    if (quantity[i] != 0) {
      if (STRAIGHT_TRACK[i]) {
        instruct(TRAIN_SLAVE, SWITCH_TRACK, 0, STRAIGHT_TRACK[i]); // Tell slave 2 to switch the track to the straight track
        delay(1000);
        instruct(TRAIN_SLAVE, MOVE, LOCATION[i], STRAIGHT_TRACK[i]); // Tell slave 2 to move forward to next ingredient at <distance[i]> relative to ultrasonic sensor
        Wire.requestFrom(TRAIN_SLAVE, 1);
        delay(500);
        while(!Wire.available()) delay(500);
        while(!Wire.read()) delay(500);
        delay(1000);
      }
      else if (!STRAIGHT_TRACK[i]) {
        instruct(TRAIN_SLAVE, SWITCH_TRACK, 0, STRAIGHT_TRACK[i]); // Tell slave 2 to switch the track to the curved track
        delay(1000);
        instruct(TRAIN_SLAVE, MOVE, LOCATION[i], STRAIGHT_TRACK[i]);
        Wire.requestFrom(TRAIN_SLAVE, 1);
        while(!Wire.available())
        while(!Wire.read())
        delay(1000);
      }
      else {
        Serial.print("Should never print this: ");
        Serial.println(i);
      }
      delay(1000);
    }
  }
}
