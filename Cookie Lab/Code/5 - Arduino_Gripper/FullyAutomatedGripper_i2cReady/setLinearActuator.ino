//Sets the rotation of the base after homing sequence has been performed

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
