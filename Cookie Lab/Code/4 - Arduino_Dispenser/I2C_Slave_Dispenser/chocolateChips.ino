void chocolateChips() {
  switch (mode) {
    case DISPENSE:
      // step one revolution  in one direction:
      Steps = quantity * 140;
      Serial.println("Number of steps = "+String(Steps));
      Serial.println("Running chocolate chips dispenser");
      Serial.println("-----------------------------------------------");
      myMotor7->step(Steps, BACKWARD, INTERLEAVE);
      myMotor7->release(); //end function be removing power from the motor
      break;
    case MOVE_UP:
      myMotor7->step(Jog, BACKWARD, DOUBLE);
      myMotor7->release(); //remove all power from the motor
      break;
    case MOVE_DOWN:
      myMotor7->step(Jog, FORWARD, DOUBLE);
      myMotor7->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
