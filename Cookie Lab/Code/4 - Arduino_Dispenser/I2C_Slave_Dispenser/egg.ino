void egg() {
  switch (mode) {
    case 0:
      // step one revolution  in one direction:
      Steps = quantity * 20;
      Serial.println("Number of steps = "+Steps);
      myMotor4->step(Steps, FORWARD, INTERLEAVE);
      Serial.println("Running egg dispenser");
      myMotor4->release(); //end function be removing power from the motor
      break;
    case 1:
      myMotor4->step(Jog, BACKWARD, DOUBLE);
      myMotor4->release(); //remove all power from the motor
      break;
    case -1:
      myMotor4->step(Jog, FORWARD, DOUBLE);
      myMotor4->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
