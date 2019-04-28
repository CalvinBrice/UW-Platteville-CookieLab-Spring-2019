void pickup() //sample movement
{
  stepper.setSpeedInMillimetersPerSecond(25.0);
  stepper.setAccelerationInMillimetersPerSecondPerSecond(25.0);
  stepper.moveToPositionInMillimeters(200.0);
  //delay(50);
}

void travel() //sample movement
{
  stepper.setSpeedInMillimetersPerSecond(25.0);
  stepper.setAccelerationInMillimetersPerSecondPerSecond(25.0);
  stepper.moveToPositionInMillimeters(100.0);
//  delay(50);
}

void sample() //sample movement
{
  //
  // set the speed and acceleration rates for the stepper motor
  //
  stepper.setSpeedInMillimetersPerSecond(20.0);
  stepper.setAccelerationInMillimetersPerSecondPerSecond(20.0);

  // Use "absolute" positioning to:
  // Move to positions: 8mm, 16mm, 24mm, then back to the home position
  //
  stepper.moveToPositionInMillimeters(8.0);
//  delay(1000);
  stepper.moveToPositionInMillimeters(100.0);
//  delay(1000);
  stepper.moveToPositionInMillimeters(200.0);
//  delay(1000);
  stepper.moveToPositionInMillimeters(0.0);
//  delay(1000);
  // increase the speed, then go to position -16mm
  stepper.setSpeedInMillimetersPerSecond(35.0);
  stepper.setAccelerationInMillimetersPerSecondPerSecond(20.0);
  stepper.moveToPositionInMillimeters(200.0);
//  delay(1000);
  // Use "relative" positioning to make several more moves, 1mm each
  //
  for (int i = 0; i < 16; i++)
  {
    stepper.moveRelativeInMillimeters(2.0);
//    delay(100);
  }
//  delay(1000);
}
