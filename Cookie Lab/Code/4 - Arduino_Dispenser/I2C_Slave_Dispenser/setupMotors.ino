void setupMotors() {

  //  class Motor {
  //    private:
  //
  //    public:
  //  }

  AFMS_0.begin();  // create with the default frequency 1.6KHz
  AFMS_1.begin();  // create with the default frequency 1.6KHz
  AFMS_2.begin();  // create with the default frequency 1.6KHz
  AFMS_3.begin();  // create with the default frequency 1.6KHz
  AFMS_4.begin();  // create with the default frequency 1.6KHz
  AFMS_5.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  //Define motor speeds globally
  myMotor2->setSpeed(60);   //  Vanilla
  myMotor3->setSpeed(60);   //  Molasses
  myMotor4->setSpeed(60);   //  Egg
  myMotor5->setSpeed(60);   //  Sugar
  myMotor6->setSpeed(30);   //  Baking Soda
  myMotor7->setSpeed(60);   //  Chocolate Chips
  myMotor8->setSpeed(60);   //  Oats
  myMotor9->setSpeed(60);   //  Flour
  myMotor10->setSpeed(60);  //  Salt
  myMotor11->setSpeed(60);  //  M&M's
  // DC motor speed (0 to 255) using PWM duty cycle.
  // This number does not control the motor speed, just the signal to the relay
  myMotor12->setSpeed(255);

  //Remove all power from the motors
  myMotor1->release();
  myMotor2->release();
  myMotor3->release();
  myMotor4->release();
  myMotor5->release();
  myMotor6->release();
  myMotor7->release();
  myMotor8->release();
  myMotor9->release();
  myMotor10->release();
  myMotor11->release();
  //myMotor12->release();
}
