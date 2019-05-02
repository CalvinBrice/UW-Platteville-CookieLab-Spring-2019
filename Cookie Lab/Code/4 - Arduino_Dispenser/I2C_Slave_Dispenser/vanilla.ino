void vanilla() {
  switch (mode) {
    case 0:
      // step one revolution  in one direction:
      Steps = quantity * 20;
      Serial.println("Number of steps = "+Steps);
      myMotor2->step(Steps, FORWARD, INTERLEAVE);
      Serial.println("Running vanilla dispenser");
      myMotor2->release(); //end function be removing power from the motor
      break;
    case 1:
      myMotor2->step(Jog, BACKWARD, DOUBLE);
      myMotor2->release(); //remove all power from the motor
      break;
    case -1:
      myMotor2->step(Jog, FORWARD, DOUBLE);
      myMotor2->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
