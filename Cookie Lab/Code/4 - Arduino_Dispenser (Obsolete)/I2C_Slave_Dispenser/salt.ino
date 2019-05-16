void salt() {
  quantity = 5;
  mode = DISPENSE;
  switch (mode) {
    case DISPENSE:
      // step one revolution  in one direction:
      Steps = quantity * 200;
//      Serial.println("Number of steps = "+String(Steps));
      Serial.println("Running salt dispenser");
//      Serial.println("-----------------------------------------------");
      myMotor10->step(Steps, FORWARD, DOUBLE);
      myMotor10->release(); //end function be removing power from the motor
      break;
    case MOVE_UP:
      myMotor10->step(Jog, FORWARD, DOUBLE);
      myMotor10->release(); //remove all power from the motor
      break;
    case MOVE_DOWN:
      myMotor10->step(Jog, BACKWARD, DOUBLE);
      myMotor10->release(); //remove all power from the motor
      break;
    default:
      break;
  }
  reset();
}
