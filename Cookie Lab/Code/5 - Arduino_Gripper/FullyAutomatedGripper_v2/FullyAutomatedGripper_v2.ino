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

#include <SpeedyStepper.h> //Library for linear actuator
#include <Adafruit_MotorShield.h> //Library for base rotation stepper
#include <Servo.h>
#include <Wire.h>

// pin assignments
int LED_PIN = 13;
int MOTOR_STEP_PIN = 6;       // --> PUL+
int MOTOR_DIRECTION_PIN = 4;  // --> DIR+
int LIMIT_SWITCH_PIN = 8;     // --> Limit switch RED wire
int FINGER_SERVO = 9;
int WRIST_SERVO = 10;
//int ROTATION_SERVO = 11;

Servo servoFinger;  // create servo object to control a servo
Servo servoWrist;  // create servo object to control a servo
SpeedyStepper stepperHeight; // create the stepper motor object

bool debug = true;          // enables serial debugging
const byte MY_ADDRESS = 3;  // i2c address of board

Adafruit_MotorShield AFMS = Adafruit_MotorShield();  // Create the motor shield object with the I2C address
Adafruit_StepperMotor *stepperBase = AFMS.getStepper(200, 2); // Connect a stepper motor with 200 steps per revolution (1.8 degree) to motor port #2 (M3 and M4)

// Structs
typedef struct {
  float pos;
  float cur;
  float minimum;
  float maximum;
} arm;

arm finger = {0, 0, 0, 180};    //initializes a finger under the arm type with (pos, cur, minimum, maximum)
arm wrist = {0, 0, 0, 180};     //wrist is limited by wiring length... do not mess with these values or you risk damage
arm height = {0, 0, 0, 370};    //maximum travel of linear actuator is 400mm - the height of the limit switch (30mm)
arm rotation = {0, 0, 0, 180};  //

void setup()
{
  //Initialize pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

  //i2c initialization
  Wire.begin(MY_ADDRESS);       // join i2c bus with address
  Wire.onReceive(receiveEvent); // register event

  //Start serial (for debugging)
  Serial.begin(9600);
  Serial.println("Gripper Arduino");

  //Initialize servos
  servoFinger.attach(FINGER_SERVO);   // attaches the servo on specified pin to the servo object
  servoWrist.attach(WRIST_SERVO);    // attaches the servo on specified pin to the servo object
  //  servo.attach(ROTATION_SERVO); // attaches the servo on specified pin to the servo object

  // connect and configure the stepper motor to its IO pins
  stepperHeight.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);
  stepperHeight.setStepsPerMillimeter(25 * 2);    // 1x microstepping

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  stepperBase->setSpeed(10);  // 10 rpm

  //----------------------------------------
  // Automation

  // set position of arm so it doesn't hit anything first
  servoFinger.write(180);
  servoWrist.write(6);

  //Begin homing procedure
  //  setHome();
  //
  //  //Debug();
  //  setHeight(200);


  //  motion(180, 6, 0, 0); //(finger, wrist, height, rotation)
  //  delay(2000);
  //  servoWrist.write(107);
  //
  //  delay(2000);
  //  servoFinger.write(90);
  //
  //  delay(2000);
  //  servoWrist.write(6);
  //
  //  delay(2000);
  //  servoFinger.write(180);
}

void loop()
{
  //State machine
  //  (actually the state machine should be on the master arduino...
  //  this one should only be receiving movement commmands and interpreting them)
  //
  //
  Serial.println("Microstep steps");
  stepperBase->step(50, FORWARD, MICROSTEP);
  stepperBase->step(50, BACKWARD, MICROSTEP);

}

void motion(int finger_pos, int wrist_pos, int height_pos, int rotation_pos) {
  // Finger
  if ( finger.minimum <= finger.pos && finger.pos <= finger.maximum) {
    //new finger position is within parameters
    servoFinger.write(180);
  }
}
