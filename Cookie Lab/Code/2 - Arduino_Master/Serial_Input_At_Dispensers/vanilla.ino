void vanilla(int quantity, int mode) {
  switch (mode) {
    case DISPENSE:
      // step one revolution  in one direction:
      Steps = quantity * 10;
//      Serial.println("Number of steps = "+String(Steps));
//      Serial.println("Running vanilla dispenser");
//      Serial.println("-----------------------------------------------");
      myMotor2->step(Steps, FORWARD, INTERLEAVE);
      myMotor2->release(); //end function be removing power from the motor
      break;
    case MOVE_UP:
      myMotor2->step(Jog, BACKWARD, DOUBLE);
      myMotor2->release(); //remove all power from the motor
      break;
    case MOVE_DOWN:
      myMotor2->step(Jog, FORWARD, DOUBLE);
      myMotor2->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
