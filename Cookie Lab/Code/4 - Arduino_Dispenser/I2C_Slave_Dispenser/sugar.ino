void sugar(int quantity) {
  switch (mode) {
    case 0:
      // step one revolution  in one direction:
//      Steps = quantity * 200;
      Serial.print("Number of steps=");
      Serial.println(Steps);
      myMotor5->step(Steps, FORWARD, DOUBLE);
      Serial.println("Running sugar dispenser");
      myMotor5->release(); //end function be removing power from the motor
      break;
    case 1: // CW
      myMotor5->step(Jog, FORWARD, DOUBLE);
      myMotor5->release(); //remove all power from the motor
      break;
    case -1: // CCW
      myMotor5->step(Jog, BACKWARD, DOUBLE);
      myMotor5->release(); //remove all power from the motor
      break;
    default:
      break;
  }
}
