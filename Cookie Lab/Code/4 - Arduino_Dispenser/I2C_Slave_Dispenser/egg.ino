void egg() {
  switch (mode) {
    case DISPENSE:
      // step one revolution  in one direction:
      Steps = quantity * 20;
      Serial.println("Number of steps = "+String(Steps));
      Serial.println("Running egg dispenser");
      Serial.println("-----------------------------------------------");
      myMotor4->step(Steps, FORWARD, INTERLEAVE);
      myMotor4->release(); //end function be removing power from the motor
      break;
    case MOVE_UP:
      myMotor4->step(Jog, BACKWARD, DOUBLE);
      myMotor4->release(); //remove all power from the motor
      break;
    case MOVE_DOWN:
      myMotor4->step(Jog, FORWARD, DOUBLE);
      myMotor4->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
