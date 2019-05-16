//----------------------------------------------------------------------------------
//  Name: Automatic Instructions
//
//  Description:
//    This function runs the automated sequence
//
//  Repository: https://github.com/CalvinBrice/UW-Platteville-CookieLab-Spring-2019-
//
//  Author: Calvin Brice
//  Date: 5/16/2019
//
//  Notes:
//    1. Ensure that the arm has a clear path upwards to home the height otherwise 
//       it will crash... and probably break
//----------------------------------------------------------------------------------

void automaticInstructions() {

  //Homing procedure
  setHome(); // homes the height of the arm
  homeRotation(); // homes the rotation of the arm

  //Position 1
  setRotation(800);
  setHeight(275);

  //Position 2
  setRotation(1100);
  servoFinger.write(CLOSE);
  delay(500);

  //Position 3
  setHeight(160); // drops arm down
  setRotation(1750);

  //Position 4
  setHeight(27);
  setPlate(1); //forward
  delay(1000);
  servoFinger.write(OPEN);
  setHeight(70);

  digitalWrite(MIXER_PIN, MIX_ON);
  delay(5000);
  digitalWrite(MIXER_PIN, MIX_OFF);
  delay(1000);

  //Position 5
  setRotation(1740);
  servoFinger.write(CLOSE);
  delay(1000);
  setPlate(0); //backward

  //Position 6
  setHeight(160);
  setRotation(800);

  //Position 7
  servoWrist.write(DOWN);
  setHeight(253);

  //Position 8
  setRotation(100);

  setLinearActuator(0); //DOWN
  delay(5000);
  setLinearActuator(1); //UP
  delay(5000);

  //Position 9
  setRotation(700);
  setHeight(156);
  delay(500);

  //Position 10
  setRotation(1105);
  setHeight(290);
  servoFinger.write(OPEN);
  setHeight(100);

}
