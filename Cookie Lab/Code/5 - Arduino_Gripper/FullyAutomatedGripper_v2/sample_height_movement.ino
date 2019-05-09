// This tab can be rewritten or deleted

void pickup() //sample movement
{
  stepperHeight.setSpeedInMillimetersPerSecond(25.0);
  stepperHeight.setAccelerationInMillimetersPerSecondPerSecond(25.0);
  stepperHeight.moveToPositionInMillimeters(200.0);
  //delay(50);
}

void travel() //sample movement
{
  stepperHeight.setSpeedInMillimetersPerSecond(25.0);
  stepperHeight.setAccelerationInMillimetersPerSecondPerSecond(25.0);
  stepperHeight.moveToPositionInMillimeters(100.0);
//  delay(50);
}

void sample() //sample movement
{
  //
  // set the speed and acceleration rates for the stepper motor
  //
  stepperHeight.setSpeedInMillimetersPerSecond(20.0);
  stepperHeight.setAccelerationInMillimetersPerSecondPerSecond(20.0);

  // Use "absolute" positioning to:
  // Move to positions: 8mm, 16mm, 24mm, then back to the home position
  //
  stepperHeight.moveToPositionInMillimeters(8.0);
//  delay(1000);
  stepperHeight.moveToPositionInMillimeters(100.0);
//  delay(1000);
  stepperHeight.moveToPositionInMillimeters(200.0);
//  delay(1000);
  stepperHeight.moveToPositionInMillimeters(0.0);
//  delay(1000);
  // increase the speed, then go to position -16mm
  stepperHeight.setSpeedInMillimetersPerSecond(35.0);
  stepperHeight.setAccelerationInMillimetersPerSecondPerSecond(20.0);
  stepperHeight.moveToPositionInMillimeters(200.0);
//  delay(1000);
  // Use "relative" positioning to make several more moves, 1mm each
  //
  for (int i = 0; i < 16; i++)
  {
    stepperHeight.moveRelativeInMillimeters(2.0);
//    delay(100);
  }
//  delay(1000);
}
