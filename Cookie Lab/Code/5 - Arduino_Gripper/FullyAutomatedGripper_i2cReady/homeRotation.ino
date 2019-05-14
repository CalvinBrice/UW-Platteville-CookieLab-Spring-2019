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
