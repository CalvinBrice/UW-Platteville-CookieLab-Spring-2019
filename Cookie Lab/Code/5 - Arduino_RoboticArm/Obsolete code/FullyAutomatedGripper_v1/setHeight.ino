//Sets the height of the linear actuator after homing sequence has been performed

void setHeight(float height) //Code to move to position in mm from home, with inputs
{
  Serial.print("Moving to absolute position: ");
  Serial.print(height);
  Serial.println("mm");
  stepper.setSpeedInMillimetersPerSecond(25.0);
  stepper.setAccelerationInMillimetersPerSecondPerSecond(25.0);
  stepper.moveToPositionInMillimeters(height);
}
