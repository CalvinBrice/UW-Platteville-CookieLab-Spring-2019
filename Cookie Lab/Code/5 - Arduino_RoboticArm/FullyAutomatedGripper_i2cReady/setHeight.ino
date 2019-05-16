//----------------------------------------------------------------------------------
//  Name: Set Height
//
//  Description:
//    This function sets the height of the linear actuator
//
//  Repository: https://github.com/CalvinBrice/UW-Platteville-CookieLab-Spring-2019-
//
//  Author: Calvin Brice
//  Date: 5/16/2019
//
//  Notes:
//    1. Ensure that the arm has a clear path upwards to home the height otherwise it will crash... and probably break
//    2. This should only be called AFTER homing sequence has been performed
//----------------------------------------------------------------------------------

void setHeight(float height) //Code to move to position in mm from home, with inputs
{
  if (0 < height && height <= maxHomingDistanceInMM) { //this makes sure that you don't crash into either end... limits should be verified
    Serial.print("Moving to absolute position: ");
    Serial.print(height);
    Serial.println("mm");
    stepperHeight.setSpeedInMillimetersPerSecond(25.0);
    stepperHeight.setAccelerationInMillimetersPerSecondPerSecond(25.0);
    stepperHeight.moveToPositionInMillimeters(height);
    heightCurrent = height;
  } else{
    Serial.println("Caution, don't exeed limits");
  }
  
}
