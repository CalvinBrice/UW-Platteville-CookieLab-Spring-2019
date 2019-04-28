//-----------------------------------------
//  Name: Fully Automated Gripper Code
//
//  Author(s): Calvin Brice, Austen Owens
//  Date: 4/27/2019
//-----------------------------------------

//This should be automated so that a sequence of positional values may be transmitted via
//i2c and translated into movements of the gripper, wrist, linear actuator, and base rotation

#include <SpeedyStepper.h>
#include <Servo.h>

// pin assignments
int LED_PIN = 13;
int MOTOR_STEP_PIN = 3;
int MOTOR_DIRECTION_PIN = 4;
int LIMIT_SWITCH_PIN = 5;

//Servo setup
int FINGER_SERVO = 9;
int WRIST_SERVO = 10;
int ROTATION_SERVO = 11;

//Linear actuator parameters
float homingSpeedInMMPerSec = 5.0;   // speed to move towards limit switch
float maxHomingDistanceInMM = 400;   // since the lead-screw is 500mm long with 400mm of travel, should never move more than that
int directionTowardHome = -1;        // direction to move toward limit switch: 1 goes positive direction, -1 backward

//Positional input parameters (pos = position)
int leftFinger_pos;   // 0~180 deg
int rightFinger_pos;  // 0~180 deg
int wrist_pos;        // 0~180 deg
int height_pos;       // 0~400 mm
int rotation_pos;     // 0~?   deg

//Positional tracking parameters (cur = current)
int leftFinger_cur;   // 0~180 deg
int rightFinger_pos;  // 0~180 deg
int wrist_pos;        // 0~180 deg
int height_pos;       // 0~400 mm
int rotation_pos;     // 0~?   deg

Servo servo;  // create servo object to control a servo
SpeedyStepper stepper; // create the stepper motor object

void setup()
{
  //Initialize pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

  //Initialize servos
  servo.attach(FINGER_SERVO);  // attaches the servo on specified pin to the servo object
  servo.attach(WRIST_SERVO);  // attaches the servo on specified pin to the servo object
  servo.attach(ROTATION_SERVO);  // attaches the servo on specified pin to the servo object

  //Start serial (for debugging)
  Serial.begin(9600);
  Serial.println("Gripper Arduino");

  // connect and configure the stepper motor to its IO pins
  stepper.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);
  stepper.setStepsPerMillimeter(25 * 2);    // 1x microstepping

  //Begin homing procedure
  setHome();
}

void loop() ///sample loop
{
  //  pickup();
  //  travel();
  //  sample();
  //  delay(100);
}
