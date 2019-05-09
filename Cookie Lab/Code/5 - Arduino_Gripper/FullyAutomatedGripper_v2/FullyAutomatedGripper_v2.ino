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

#include <SpeedyStepper.h>
#include <Servo.h>
#include <Wire.h>

bool debug = true;          // enables serial debugging
const byte MY_ADDRESS = 3;  // i2c address of board

// pin assignments
int LED_PIN = 13;
int MOTOR_STEP_PIN = 3; // --> PUL+
int MOTOR_DIRECTION_PIN = 4; // --> DIR+
int LIMIT_SWITCH_PIN = 5;// --> Limit switch RED wire
int FINGER_SERVO = 9;
int WRIST_SERVO = 10;
int ROTATION_SERVO = 11;

//Rewrite so that these are stored in an array... or a struct
//this will allow for easier access and less variables to keep track of


// Structs
struct armElement {
  float set; //sets location of future position
  float current; // holds current positional value
  int8_t minmax[2]; // limit parameters
}

//Positional input parameters and initialization (pos = position)
int finger_pos = 0;     // 0~180 deg
int wrist_pos = 0;      // 0~180 deg
int height_pos = 0;     // 0~400 mm
int rotation_pos = 0;   // 0~?   deg

//Positional tracking parameters (cur = current)
int finger_cur = finger_pos;       // 0~180 deg
int wrist_cur = wrist_pos;         // 0~180 deg
int height_cur = height_pos;       // 0~400 mm
int rotation_cur = rotation_pos;   // 0~?   deg

//Positional range parameters (min/max)
int finger_par[] = {0, 180};       // 0~180 deg
int wrist_par[] = {6, 107};        // 0~180 deg
int height_par[] = {0, 400};       // 0~400 mm
int rotation_par[] = {0, 180};     // 0~?   deg

Servo servo;  // create servo object to control a servo
SpeedyStepper stepper; // create the stepper motor object

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
  servo.attach(FINGER_SERVO);   // attaches the servo on specified pin to the servo object
  servo.attach(WRIST_SERVO);    // attaches the servo on specified pin to the servo object
  servo.attach(ROTATION_SERVO); // attaches the servo on specified pin to the servo object

  // connect and configure the stepper motor to its IO pins
  stepper.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);
  stepper.setStepsPerMillimeter(25 * 2);    // 1x microstepping

  // set position of arm so it doesn't hit anything first


  //Begin homing procedure
  //setHome();

  Debug();
  //setHeight(250);
  //Motion(finger_pos, wrist_pos, height_pos, rotation_pos);
}

void loop()
{
  //State machine
  //  (actually the state machine should be on the master arduino...
  //  this one should only be receiving movement commmands and interpreting them)


}

void motion(int finger_pos, int wrist_pos, int height_pos, int rotation_pos) {
  // Finger
  if ( == finger_pos && finger_pos == d)
}
