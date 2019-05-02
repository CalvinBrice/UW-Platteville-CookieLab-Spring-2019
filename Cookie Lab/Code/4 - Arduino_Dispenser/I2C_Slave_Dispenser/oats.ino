void oats(int quantity) {
  switch (mode) {
    case 0:
      // step one revolution  in one direction:
      Steps = quantity * 140;
      Serial.print("Number of steps=");
      Serial.println(Steps);
      myMotor8->step(Steps, BACKWARD, INTERLEAVE);
      Serial.println("Running oatmeal dispenser");
      myMotor8->release(); //end function be removing power from the motor
      break;
    case 1:
      myMotor8->step(Jog, BACKWARD, DOUBLE);
      myMotor8->release(); //remove all power from the motor
      break;
    case -1:
      myMotor8->step(Jog, FORWARD, DOUBLE);
      myMotor8->release(); //remove all power from the motor
      break;
    default:
      break;
  }
}
