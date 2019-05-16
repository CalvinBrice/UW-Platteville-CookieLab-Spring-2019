//----------------------------------------------------------------------------------
//  Name: Set Plate
//
//  Description:
//    This function sets the positon of the plate that slides underneath the mixer
//
//  Repository: https://github.com/CalvinBrice/UW-Platteville-CookieLab-Spring-2019-
//
//  Author: Calvin Brice
//  Date: 5/16/2019
//
//  Notes:
//    1. Front = 1
//    2. Back = 0
//    3. The position is controlled with two servos that are positioned opposite 
//       eachother
//----------------------------------------------------------------------------------

void setPlate(boolean value)
{
  if (value == 1) {
    Serial.println("recieved: Plate FRONT");
    servoPlate1.write(10);
  }

  if (value == 0) {
    Serial.println("recieved: Plate BACK");
    servoPlate1.write(180);
  }

}
