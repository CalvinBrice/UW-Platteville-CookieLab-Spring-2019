void salt() {
  switch (mode) {
    case 0:
      // step one revolution  in one direction:
      Steps = quantity * 200;
      Serial.println("Number of steps = "+Steps);
      myMotor10->step(Steps, FORWARD, DOUBLE);
      Serial.println("Running salt dispenser");
      myMotor10->release(); //end function be removing power from the motor
      break;
    case 1:
      myMotor10->step(Jog, FORWARD, DOUBLE);
      myMotor10->release(); //remove all power from the motor
      break;
    case -1:
      myMotor10->step(Jog, BACKWARD, DOUBLE);
      myMotor10->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
