//Sets the rotation of the base after homing sequence has been performed

void setPlate(boolean value) //Code to move to position in mm from home, with inputs
{
  int rotMin = 30;
  int rotTravel = 180;
  
  int rot = 180 - rotTravel;

  if (value == 1) {
    Serial.println("Plate: FRONT");
    servoPlate1.write(180 - rot);
    servoPlate2.write(rotMin + rot);
  }

  if (value == 0) {
    Serial.println("Plate: BACK");
    servoPlate1.write(rotMin);
    servoPlate2.write(180-rotMin);
  }

}
