void chocolateChips() {
  switch (mode) {
    case 0:
      // step one revolution  in one direction:
      Steps = quantity * 140;
      Serial.println("Number of steps = "+Steps);
      myMotor7->step(Steps, BACKWARD, INTERLEAVE);
      Serial.println("Running chocolate chips dispenser");
      myMotor7->release(); //end function be removing power from the motor
      break;
    case 1:
      myMotor7->step(Jog, BACKWARD, DOUBLE);
      myMotor7->release(); //remove all power from the motor
      break;
    case -1:
      myMotor7->step(Jog, FORWARD, DOUBLE);
      myMotor7->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
