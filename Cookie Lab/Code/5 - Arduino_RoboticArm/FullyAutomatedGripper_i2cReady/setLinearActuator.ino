//----------------------------------------------------------------------------------
//  Name: Set Linear Actuator
//
//  Description:
//    This function sets the positon of the linear actuator for the extruder 
//
//  Repository: https://github.com/CalvinBrice/UW-Platteville-CookieLab-Spring-2019-
//
//  Author: Calvin Brice
//  Date: 5/16/2019
//
//  Notes:
//    1. Up = 1
//    2. Down = 0
//    3. the position is controlled with two relays turned on and off
//----------------------------------------------------------------------------------

void setLinearActuator(boolean value) //Code to move to position in mm from home, with inputs
{
  if (value == 1) {
    Serial.println("Linear Actuator: UP");
    digitalWrite(LINEAR_ACTUATOR_UP, HIGH); 
    digitalWrite(LINEAR_ACTUATOR_DOWN, LOW);  
  }

  if (value == 0) {
    Serial.println("Linear Actuator: DOWN");
    digitalWrite(LINEAR_ACTUATOR_UP, LOW); 
    digitalWrite(LINEAR_ACTUATOR_DOWN, HIGH);  
  }

}
