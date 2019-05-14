void setCartToOrigin() {
  digitalWrite(UPower1, HIGH); // Turn on ultrasonic sensor #1

  if (analogRead(URead1) > 100) {
    //    Serial.println("Reading U1");
    digitalWrite(switchPin, HIGH); // Set track to curved side
    digitalWrite(cartDirectionPin, LOW); // Set cart direction to reverse
    analogWrite(trackPWM, CART_GO); // Tell cart to go
    while (!digitalRead(capSensorPin)); // While the inductive sensor is 0, do nothing
    analogWrite(trackPWM, CART_STOP); // Tell cart to stop
  }
  digitalWrite(UPower1, LOW); // Turn off ultrasonic sensor #1
  digitalWrite(UPower2, HIGH); // Turn on ultrasonic sensor #2
  
  if (analogRead(URead2) > 100) {
    //    Serial.println("Reading U2");
    digitalWrite(switchPin, LOW); // Set track to straight side
    digitalWrite(cartDirectionPin, LOW); // Set cart direction to reverse
    analogWrite(trackPWM, CART_GO); // Tell cart to go
    while (!digitalRead(capSensorPin)); // While the inductive sensor is 0, do nothing
    analogWrite(trackPWM, CART_STOP); // Tell cart to stop
  }

  digitalWrite(UPower2, LOW); // Turn off ultrasonic sensor #2

  if (!digitalRead(capSensorPin)) { // If cart not triggering inductive sensor
    digitalWrite(cartDirectionPin, HIGH); // Set the cart direction to forward
    analogWrite(trackPWM, HIGH); // Tell the cart to go
  }

  if (digitalRead(capSensorPin)) return; // If the cart is at the inductive sensor, exit function
  else setCartToOrigin(); // Otherwise, go through function again
}

