//Sets the height of the linear actuator after homing sequence has been performed

void setHeight(float height) //Code to move to position in mm from home, with inputs
{
  if (0 < height && height <= maxHomingDistanceInMM) {
    Serial.print("Moving to absolute position: ");
    Serial.print(height);
    Serial.println("mm");
    stepperHeight.setSpeedInMillimetersPerSecond(30.0);
    stepperHeight.setAccelerationInMillimetersPerSecondPerSecond(25.0);
    stepperHeight.moveToPositionInMillimeters(height);
    heightCurrent = height;
  } else{
    Serial.println("Caution, don't exeed limits");
  }
  
}
