void butter(int quantity, int mode) {
  switch (mode) {
    case DISPENSE:
      // step one revolution  in one direction:
      Steps = quantity * 100; //calibrate the multiplication factor as necessary to match the dispensing scale shown on the interface
//      Serial.println("Number of steps = "+String(Steps));
//      Serial.println("Running butter dispenser");
//      Serial.println("-----------------------------------------------");
      myMotor1->setSpeed(100);
      myMotor1->step(Steps, FORWARD, DOUBLE);
      myMotor1->release(); //end function be removing power from the motor
      break;
    case MOVE_UP:
      myMotor1->setSpeed(1500);
      myMotor1->step(ButterJog, FORWARD, DOUBLE);
      myMotor1->release(); //remove all power from the motor
      break;
    case MOVE_DOWN:
      myMotor1->setSpeed(1500);
      myMotor1->step(ButterJog, BACKWARD, DOUBLE);
      myMotor1->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
