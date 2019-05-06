void mms() {
  switch (mode) {
    case DISPENSE:
      // step one revolution  in one direction:
      Steps = quantity * 140;
      Serial.println("Number of steps = "+String(Steps));
      Serial.println("Running MMs dispenser");
      Serial.println("-----------------------------------------------");
      myMotor11->step(Steps, FORWARD, INTERLEAVE);
      myMotor11->release(); //end function by removing power from the motor
      break;
    case MOVE_UP:
      myMotor11->step(Jog, FORWARD, DOUBLE);
      myMotor11->release(); //remove all power from the motor
      break;
    case MOVE_DOWN:
      myMotor11->step(Jog, BACKWARD, DOUBLE);
      myMotor11->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
