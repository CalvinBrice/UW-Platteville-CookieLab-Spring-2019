//-----------------------------------------
//  Name: Fully Automated Gripper Code
//
//  Repository: https://github.com/CalvinBrice/UW-Platteville-CookieLab-Spring-2019-
//
//  Author(s): Calvin Brice, Austen Owens
//  Date: 5/7/2019
//-----------------------------------------

// This should be automated so that a sequence of positional values may be transmitted via
// i2c and translated into movements of the gripper, wrist, linear actuator, and base rotation
// Format of messages to be received is:
// (int FINGER, int WRIST, int HEIGHT, int, ROTATION)

//Fix delay with millis

#include <SpeedyStepper.h> //Library for linear actuator
#include <Adafruit_MotorShield.h> //Library for base rotation stepper
#include <Servo.h>
#include <Wire.h>

bool debug = true;          // enables serial debugging
const byte MY_ADDRESS = 3;  // i2c address of board

// pin assignments
int PLATE_SERVO1 = 5;
int PLATE_SERVO2 = 11;

int MOTOR_STEP_PIN = 6;       // --> PUL+
int MOTOR_DIRECTION_PIN = 4;  // --> DIR+
int LIMIT_SWITCH_PIN = 8;     // --> Limit switch RED wire

int FINGER_SERVO = 9;
int WRIST_SERVO = 10;
int LED_PIN = 13;

Servo servoFinger;  // create servo object to control a servo
Servo servoWrist;  // create servo object to control a servo
Servo servoPlate1;  // create servo object to control a servo
Servo servoPlate2;  // create servo object to control a servo

SpeedyStepper stepperHeight; // create the stepper motor object

Adafruit_MotorShield AFMS = Adafruit_MotorShield();  // Create the motor shield object with the I2C address
Adafruit_StepperMotor *stepperBase = AFMS.getStepper(200, 2); // Connect a stepper motor with 200 steps per revolution (1.8 degree) to motor port #2 (M3 and M4)

//---------------------------------------------------------------------------

enum GRIP {OPEN = 180, CLOSE = 90};
enum WRIST {UP = 5, DOWN = 158};
enum PLATE {FRONT = 0, BACK = 180};
enum MIXER {ON = HIGH, OFF = LOW};
GRIP gripper = OPEN;  // declares object of gripper and sets initial position
WRIST wrist = UP;     // declares object of wrist and sets initial position
PLATE plate = BACK;   // declares object of plate and sets initial position
MIXER mixer = OFF;    // declares object of mixer and sets initial state

void setup()
{

  //Start serial (for debugging)
  Serial.begin(9600);
  Serial.println("Gripper Arduino");
  pinMode(LED_PIN, OUTPUT);

  //i2c initialization
  Wire.begin(MY_ADDRESS); // join i2c bus with address
  Wire.onReceive(receiveEvent); // register event


  //Initialize servos
  servoFinger.attach(FINGER_SERVO, 0 , 180);  // attaches the servo on specified pin to the servo object
  servoWrist.attach(WRIST_SERVO, 0, 180);
  servoPlate1.attach(PLATE_SERVO1, 0, 180);
  servoPlate2.attach(PLATE_SERVO2, 0, 180);

  // connect and configure the stepper motor to its IO pins
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);
  stepperHeight.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);
  stepperHeight.setStepsPerMillimeter(25 * 2);    // 1x microstepping

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  stepperBase->setSpeed(80);  // 80 rpm

  //----------------------------------------
  // Automation

  // set position of arm so it doesn't hit anything first
  servoFinger.write(OPEN);
  servoWrist.write(UP);

  //stepperBase->step(100, FORWARD, SINGLE); //moves arm to home position (it is normal to run it agains the upright post to zero the postion)

  //Begin homing procedure of linear actuator
  //setHome();

  //  setHeight(200); // drops arm down
  //  delay(2000);
  //  startupSequence();

  //-------------------------------------
  Serial.println("done with setup");
}


void startupSequence() {
  Serial.println("");
  Serial.println("Start up sequence");

  //setHeight(200); // drops arm down
  //Serial.println("height: 200");
  //delay(1000);

  //    wrist = DOWN;
  servoWrist.write(DOWN);
  Serial.println("wrist: DOWN");
  delay(2000);
  //
  //  gripper = CLOSE;
  //  Serial.println("gripper: CLOSE");
  //  delay(1000);

  //  wrist = UP;
  servoWrist.write(UP);
  Serial.println("wrist: UP");
  //  delay(1000);
  //
  //  gripper = OPEN;
  //  Serial.println("gripper: OPEN");
  //  delay(1000);

  Serial.println("done");
}



void loop()
{
  if (Serial.available() > 0) {
    // read incoming serial data:
    char inChar = Serial.read();
    switch (inChar) {
      case '1':
        Serial.println("received: 1 = home");
        setHome();

        break;
      case '2':
        Serial.println("received: 2");
        startupSequence();
        break;
      case '3':
        Serial.println("received: 3");
        setHeight(200); // drops arm down
        break;
      case '4':
        Serial.println("received: 3");
        setHeight(150); // drops arm down
        break;
      case 'a':
        Serial.println("received: CCW");
        stepperBase->step(100, FORWARD, SINGLE); //Rotates CCW
        break;
      case 'd':
        Serial.println("received: CW");
        stepperBase->step(100, BACKWARD, SINGLE); //Rotates CCW
        break;
      default:
        Serial.println("Not a valid command");
        break;
    }
  }
}
