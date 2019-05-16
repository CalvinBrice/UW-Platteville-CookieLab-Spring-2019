void setHeight(float z) //Code to move to position in mm from home, with inputs
{
  stepper.setSpeedInMillimetersPerSecond(25.0);
  stepper.setAccelerationInMillimetersPerSecondPerSecond(25.0);
  stepper.moveToPositionInMillimeters(z);
}
