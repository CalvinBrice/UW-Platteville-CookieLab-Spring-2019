//Sets the rotation of the base after homing sequence has been performed

void setRotation(int rotationNew) //Code to move to position in mm from home, with inputs
{
  if (0 < rotationNew && rotationNew <= rotationMax) {
    Serial.print("Moving to absolute position: ");
    Serial.println(rotationNew);

    float travel = rotationNew - rotationCurrent;

    if (travel > 0 ) {
      stepperBase->step(abs(travel), FORWARD, DOUBLE); //Rotates CCW
      stepperBase->release(); //remove all power from the motor
    } else {
      stepperBase->step(abs(travel), BACKWARD, DOUBLE); //Rotates CCW
      stepperBase->release(); //remove all power from the motor
    }
    rotationCurrent = rotationNew;
  } else {
    Serial.println("Caution, don't exeed limits");
  }

}
