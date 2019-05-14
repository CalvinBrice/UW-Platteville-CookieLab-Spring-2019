void molasses(int quantity, int mode) {
  switch (mode) {
    case DISPENSE:
      // step one revolution  in one direction:
      Steps = quantity * 100;
//      Serial.println("Number of steps = "+String(Steps));
//      Serial.println("Running molasses dispenser");
//      Serial.println("-----------------------------------------------");
      myMotor3->step(Steps, FORWARD, INTERLEAVE);
      myMotor3->release(); //end function be removing power from the motor
      break;
    case MOVE_UP:
      myMotor3->step(Jog, FORWARD, DOUBLE);
      myMotor3->release(); //remove all power from the motor
      break;
    case MOVE_DOWN:
      myMotor3->step(Jog, BACKWARD, DOUBLE);
      myMotor3->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
