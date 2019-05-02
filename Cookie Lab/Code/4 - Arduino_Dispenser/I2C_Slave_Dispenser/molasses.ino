void molasses(int quantity) {
  switch (mode) {
    case 0:
      // step one revolution  in one direction:
      Steps = quantity * 20;
      Serial.print("Number of steps=");
      Serial.println(Steps);
      myMotor3->step(Steps, FORWARD, INTERLEAVE);
      Serial.println("Running molasses dispenser");
      myMotor3->release(); //end function be removing power from the motor
      break;
    case 1:
      myMotor3->step(Jog, BACKWARD, DOUBLE);
      myMotor3->release(); //remove all power from the motor
      break;
    case -1:
      myMotor3->step(Jog, FORWARD, DOUBLE);
      myMotor3->release(); //remove all power from the motor
      break;
    default:
      break;
  }
}
