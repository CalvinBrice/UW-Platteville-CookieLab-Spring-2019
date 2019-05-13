void bakingSoda(int quantity, int mode) {
  switch (mode) {
    case DISPENSE:
      // step one revolution  in one direction:
      Steps = quantity * 10;
//      Serial.println("Number of steps = "+String(Steps));
//      Serial.println("Running baking soda dispenser");
//      Serial.println("-----------------------------------------------");
      myMotor6->step(Steps, FORWARD, INTERLEAVE);
      delay(250);
      myMotor6->step(Steps, BACKWARD, INTERLEAVE);
      myMotor6->release(); //end function be removing power from the motor
      break;
    case MOVE_UP:
      myMotor6->step(BakingSodaJog, FORWARD, DOUBLE);
      myMotor6->release(); //remove all power from the motor
      break;
    case MOVE_DOWN:
      myMotor6->step(BakingSodaJog, BACKWARD, DOUBLE);
      myMotor6->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
