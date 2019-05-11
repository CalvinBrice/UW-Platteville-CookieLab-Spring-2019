//Linear actuator parameters
float homingSpeedInMMPerSec = 5.0;   // speed to move towards limit switch
float maxHomingDistanceInMM = height.maximum; //400;   // since the lead-screw is 500mm long with 400mm of travel, should never move more than that
int directionTowardHome = -1;        // direction to move toward limit switch: 1 goes positive direction, -1 backward

void setHome()  //Function to home with limit switch
{
  Serial.println("Moving to home position");
  // set the speed and acceleration rates for the stepper motor
  stepperHeight.setSpeedInMillimetersPerSecond(25.0);
  stepperHeight.setAccelerationInMillimetersPerSecondPerSecond(10.0);

  // move the motor toward the limit switch to find the "Home" position
  
  if (stepperHeight.moveToHomeInMillimeters(directionTowardHome, homingSpeedInMMPerSec, maxHomingDistanceInMM, LIMIT_SWITCH_PIN) != true)
  {
    // this code is executed only if homing fails because it has moved farther
    // than maxHomingDistanceInMM and never finds the limit switch, blink the
    // LED fast forever indicating a problem
    while (true)
    {
      Serial.println("Error homing");
      digitalWrite(LED_PIN, HIGH);
      delay(50);
      digitalWrite(LED_PIN, LOW);
      delay(50);
    }
  }
Serial.println("Successfully homed");

  // homing is now complete, the motor is stopped at position 0mm
  //delay(500);
  // if you want your 0 origin someplace else, you can change it
  //
  //stepperHeight.setCurrentPositionInMillimeters(0);
}
