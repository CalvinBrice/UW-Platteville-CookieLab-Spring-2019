void bakingSoda() {
  switch (mode) {
    case 0:
      // step one revolution  in one direction:
      Steps = quantity * 40;
      Serial.println("Number of steps = "+Steps);
      myMotor6->step(Steps, FORWARD, INTERLEAVE);
      delay(250);
      myMotor6->step(Steps, BACKWARD, INTERLEAVE);
      Serial.println("Running baking soda dispenser");
      myMotor6->release(); //end function be removing power from the motor
      break;
    case 1:
      myMotor6->step(BakingSodaJog, FORWARD, DOUBLE);
      myMotor6->release(); //remove all power from the motor
      break;
    case -1:
      myMotor6->step(BakingSodaJog, BACKWARD, DOUBLE);
      myMotor6->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
