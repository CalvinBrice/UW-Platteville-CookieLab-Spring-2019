//----------------------------------------------------------------------------------
//  Name: Set Home
//
//  Description:
//    This function homes the height of the linear actuator
//
//  Repository: https://github.com/CalvinBrice/UW-Platteville-CookieLab-Spring-2019-
//
//  Author: Calvin Brice
//  Date: 5/16/2019
//
//  Notes:
//    1. Ensure that the arm has a clear path upwards to home the height otherwise it will crash... and probably break
//    2. This should only be called at least once BEFORE the set height function
//----------------------------------------------------------------------------------


//Linear actuator parameters
float homingSpeedInMMPerSec = 8.0;   // speed to move towards limit switch
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
      //delay(50);
      digitalWrite(LED_PIN, LOW);
      //delay(50);
    }
  }
  
  heightCurrent = 0;
  Serial.println("Successfully homed");

  // homing is now complete, the motor is stopped at position 0mm
  //delay(500);
  // if you want your 0 origin someplace else, you can change it
  //
  //stepperHeight.setCurrentPositionInMillimeters(0);
}
