void sugar(int quantity, int mode) {
  switch (mode) {
    case DISPENSE:
      // step one revolution  in one direction:
      Steps = quantity * 10;
//      Serial.println("Number of steps = "+String(Steps));
//      Serial.println("Running sugar dispenser");
//      Serial.println("-----------------------------------------------");
      myMotor5->step(Steps, FORWARD, DOUBLE);
      myMotor5->release(); //end function be removing power from the motor
      break;
    case MOVE_UP: // CW
      myMotor5->step(Jog, FORWARD, DOUBLE);
      myMotor5->release(); //remove all power from the motor
      break;
    case MOVE_DOWN: // CCW
      myMotor5->step(Jog, BACKWARD, DOUBLE);
      myMotor5->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
