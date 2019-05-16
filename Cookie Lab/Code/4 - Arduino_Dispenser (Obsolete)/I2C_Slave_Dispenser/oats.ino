void oats() {
  switch (mode) {
    case DISPENSE:
      // step one revolution  in one direction:
      Steps = quantity * 140;
//      Serial.println("Number of steps = "+String(Steps));
      Serial.println("Running oatmeal dispenser");
//      Serial.println("-----------------------------------------------");
      myMotor8->step(Steps, BACKWARD, INTERLEAVE);
      myMotor8->release(); //end function be removing power from the motor
      break;
    case MOVE_UP:
      myMotor8->step(Jog, BACKWARD, DOUBLE);
      myMotor8->release(); //remove all power from the motor
      break;
    case MOVE_DOWN:
      myMotor8->step(Jog, FORWARD, DOUBLE);
      myMotor8->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
