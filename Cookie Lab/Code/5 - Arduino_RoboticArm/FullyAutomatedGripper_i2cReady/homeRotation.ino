//----------------------------------------------------------------------------------
//  Name: Home Rotation
//
//  Description:
//    This function "homes" the positional rotation of the arm
//
//  Repository: https://github.com/CalvinBrice/UW-Platteville-CookieLab-Spring-2019-
//
//  Author: Calvin Brice
//  Date: 5/16/2019
//
//  Notes:
//    1. Ensure that the arm has a clear path upwards to home the height otherwise it will crash... and probably break
//----------------------------------------------------------------------------------

void homeRotation() {
  Serial.println("received: home base");
  setHeight(120);
  //home base (basically rotate until it runs into the post)
  stepperBase->step(1350, BACKWARD, DOUBLE); //Rotates CCW
  stepperBase->step(50, FORWARD, DOUBLE); //Rotates CCW
  //stepperBase->release(); //remove all power from the motor
  //set base zero
  rotationCurrent = 565;  //rotation tracking
  Serial.print("rotationCurrent = ");
  Serial.println(rotationCurrent);
}
