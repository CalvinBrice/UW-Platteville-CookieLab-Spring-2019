void setCartToOrigin() {
  digitalWrite(UPower1, HIGH);

  if (analogRead(URead1) != 0) {
    digitalWrite(switchPin, HIGH);
    digitalWrite(cartDirectionPin, LOW);
    analogWrite(trackPWM, CART_GO);
    while (!digitalRead(capSensorPin));
    analogWrite(trackPWM, CART_STOP);
  }

  digitalWrite(UPower1, LOW);
  digitalWrite(UPower2, HIGH);

  if (analogRead(URead2 != 0)) {
    digitalWrite(switchPin, LOW);
    digitalWrite(cartDirectionPin, LOW);
    analogWrite(trackPWM, CART_GO);
    while (!digitalRead(capSensorPin));
    analogWrite(trackPWM, CART_STOP);
  }

  digitalWrite(UPower2, LOW);

  if (!digitalRead(capSensorPin)) {
    digitalWrite(cartDirectionPin, HIGH);
    analogWrite(trackPWM, HIGH);
  }

  if (digitalRead(capSensorPin)) return;
  else setCartToOrigin();
}

