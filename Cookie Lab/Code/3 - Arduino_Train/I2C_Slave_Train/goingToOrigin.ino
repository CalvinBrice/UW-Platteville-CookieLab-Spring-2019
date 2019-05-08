void goingToOrigin(){
  if (!digitalRead(capSensorPin)) { // Sets the cart moving backwards and quickly
    digitalWrite(cartDirectionPin, LOW);
    analogWrite(trackPWM, FAST);
  }
  while (!digitalRead(capSensorPin)) analogWrite(trackPWM, FAST); // Keep going backwards until it reaches the capacitive sensor
  analogWrite(trackPWM, STOP); // Stops the cart
}
