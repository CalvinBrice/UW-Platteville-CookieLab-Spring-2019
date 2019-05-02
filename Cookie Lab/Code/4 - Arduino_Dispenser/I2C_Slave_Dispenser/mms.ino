void mms() {
  switch (mode) {
    case 0:
      // step one revolution  in one direction:
      Steps = quantity * 140;
      Serial.println("Number of steps = "+Steps);
      myMotor11->step(Steps, FORWARD, INTERLEAVE);
      Serial.println("Running MMs dispenser");
      myMotor11->release(); //end function be removing power from the motor
      break;
    case 1:
      myMotor11->step(Jog, FORWARD, DOUBLE);
      myMotor11->release(); //remove all power from the motor
      break;
    case -1:
      myMotor11->step(Jog, BACKWARD, DOUBLE);
      myMotor11->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
