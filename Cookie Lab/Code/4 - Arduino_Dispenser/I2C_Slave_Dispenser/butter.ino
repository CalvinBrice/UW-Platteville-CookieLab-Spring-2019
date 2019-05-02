void butter(int quantity) {
  switch (mode) {
    case 0:
      // step one revolution  in one direction:
      Steps = quantity * 100; //calibrate the multiplication factor as necessary to match the dispensing scale shown on the interface
      Serial.print("Number of steps=");
      Serial.println(Steps);
      myMotor1->setSpeed(100);
      myMotor1->step(Steps, FORWARD, DOUBLE);
      Serial.println("Running butter dispenser");
      myMotor1->release(); //end function be removing power from the motor
      break;
    case 1:
      myMotor1->setSpeed(1500);
      myMotor1->step(ButterJog, BACKWARD, DOUBLE);
      myMotor1->release(); //remove all power from the motor
      break;
    case -1:
      myMotor1->setSpeed(1500);
      myMotor1->step(ButterJog, FORWARD, DOUBLE);
      myMotor1->release(); //remove all power from the motor
      break;
    default:
      break;
  }
}
