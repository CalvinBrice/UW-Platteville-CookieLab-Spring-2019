void flour() {
  switch (mode) {
    case 0:
      // step one revolution  in one direction:
      Steps = quantity * 140;
      Serial.println("Number of steps = "+Steps);
      myMotor12->run(FORWARD); //Starting the agitator and delaying for one second
      delay(1000);
      myMotor9->step(Steps, FORWARD, INTERLEAVE); //Starting the flour dispenser
      Serial.println("Running flour dispenser and agitator");
      myMotor9->release(); //end function be removing power from the motor
      delay(2000); //Delaying 5 seconds before shutting off the agitator
      myMotor12->run(RELEASE); //end function be removing power from the motor
      break;
    case 1:
      myMotor9->step(Jog, FORWARD, DOUBLE);
      myMotor9->release(); //remove all power from the motor
      break;
    case -1:
      myMotor9->step(Jog, BACKWARD, DOUBLE);
      myMotor9->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
