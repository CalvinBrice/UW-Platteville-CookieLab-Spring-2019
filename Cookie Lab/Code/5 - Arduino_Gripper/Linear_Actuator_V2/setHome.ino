void setHome()  //Function to home with limit switch
{
  // set the speed and acceleration rates for the stepper motor
  stepper.setSpeedInMillimetersPerSecond(25.0);
  stepper.setAccelerationInMillimetersPerSecondPerSecond(10.0);

  // move the motor toward the limit switch to find the "Home" position
  const float homingSpeedInMMPerSec = 5.0;
  const float maxHomingDistanceInMM = 400;   // since my lead-screw is 500mm long with 400mm of travel, should never move more than that
  const int directionTowardHome = -1;        // direction to move toward limit switch: 1 goes positive direction, -1 backward

  if (stepper.moveToHomeInMillimeters(directionTowardHome, homingSpeedInMMPerSec, maxHomingDistanceInMM, LIMIT_SWITCH_PIN) != true)
  {
    // this code is executed only if homing fails because it has moved farther
    // than maxHomingDistanceInMM and never finds the limit switch, blink the
    // LED fast forever indicating a problem
    while (true)
    {
      digitalWrite(LED_PIN, HIGH);
      delay(50);
      digitalWrite(LED_PIN, LOW);
      delay(50);
    }
  }

  // homing is now complete, the motor is stopped at position 0mm
  //delay(500);
  // if you want your 0 origin someplace else, you can change it
  //
  //stepper.setCurrentPositionInMillimeters(0);

}
