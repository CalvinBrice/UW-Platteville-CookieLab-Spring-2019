//----------------------------------------------------------------------------------
//  Name: Fully Automated Robotic Arm Code

//  Author(s): Calvin Brice, Austen Owens
//  Date: 5/16/2019
//
//  Description:
//    This function runs the automated sequence
//
//  Repository: https://github.com/CalvinBrice/UW-Platteville-CookieLab-Spring-2019-
//
//  Notes:
//    1. Fix delay function with "blink without delay" technique using millis in the
//        future... some code is already implimented
//    2. Look under loop code for manual control instructions via serial
//    3. To start the automated sequence, type "9" into the serial monitor and press 
//        enter
//----------------------------------------------------------------------------------

// --- Import correct libraries ---
#include <SpeedyStepper.h> //Library for linear actuator
#include <Adafruit_MotorShield.h> //Library for base rotation stepper
#include <Servo.h>
#include <Wire.h>

bool mainInControl = true;     // If it's false, then the arm is in control
bool debug = true;             // enables serial debugging
enum Slaves {MASTER = 0x08, CART = 0x09, ARM = 0X10}; // Using these for i2c addresses
const byte MY_ADDRESS = 0x10;  // i2c address of board

float maxHomingDistanceInMM = 400;   // since the lead-screw is 500mm long with 400mm of travel, should never move more than that
float rotationMax = 10000;
int stepSize = 50; // used to increment base rotation
int heightCurrent;        //position tracking
int rotationCurrent;      //rotation tracking


// --- pin assignments ---
int PLATE_SERVO1 = 5;         // --> Yellow tape
int PLATE_SERVO2 = 3;        // --> Orange tape

int MOTOR_STEP_PIN = 6;       // --> PUL+ (White wire from motor)
int MOTOR_DIRECTION_PIN = 4;  // --> DIR+ (Black wire from motor)
int LIMIT_SWITCH_PIN = 8;     // --> Limit switch RED wire (Black goes to a ground)

int MIXER_PIN = A0;

int LINEAR_ACTUATOR_UP = A1;  // -->  Yellow
int LINEAR_ACTUATOR_DOWN = A2;// -->  Blue

int FINGER_SERVO = 9;         // --> Teal wire
int WRIST_SERVO = 10;         // --> Blue wire
int LED_PIN = 13;


// --- initializing servos and motor objects ---
Servo servoFinger;  // create servo object to control a servo
Servo servoWrist;
Servo servoPlate1;
Servo servoPlate2;

// Uses <Adafruit_MotorShield.h> library
SpeedyStepper stepperHeight; // create the stepper motor object for the linear actuator (NEMA 23 motor)

// Uses <SpeedyStepper.h> library
Adafruit_MotorShield AFMS(0x66);  // 0x66 Create the motor shield object with the I2C address (verify it isn't used by other shields for dispenser)
Adafruit_StepperMotor *stepperBase = AFMS.getStepper(400, 2); // Connect a stepper motor with 400 steps per revolution (1.8 degree) to motor port #2 (M3 and M4)


// --- servo input parameters... ---
enum GRIP {OPEN = 180, CLOSE = 25};
enum WRIST {UP = 12, DOWN = 165};
enum MIXER {MIX_ON = HIGH, MIX_OFF = LOW};

GRIP gripper = OPEN;  // declares object of gripper and sets initial position
WRIST wrist = UP;     // declares object of wrist and sets initial position
MIXER mixer = MIX_OFF;    // declares object of mixer and sets initial state


// --- replaces delay() because that may cause issues ---

// See arduino example "blinkWithoutDelay"
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)
//----------------------------------------------------------------------------------

void setup()
{

  //Start serial (for debugging)
  Serial.begin(9600);
  Serial.println("Robotic Arm - Arduino");
  pinMode(LED_PIN, OUTPUT); //Not really necessary

  //i2c initialization
  Wire.begin(MY_ADDRESS); // join i2c bus with address
  Wire.onReceive(receiveEvent); // register event

  //Set relay pin for mixer
  pinMode(MIXER_PIN, OUTPUT);

  //Set relay pins for linear actuator
  pinMode(LINEAR_ACTUATOR_UP, OUTPUT);
  pinMode(LINEAR_ACTUATOR_DOWN, OUTPUT);

  //Initialize servos
  servoFinger.attach(FINGER_SERVO, 0 , 180);  // attaches the servo on specified pin to the servo object with output range from 0 to 180
  servoWrist.attach(WRIST_SERVO, 0, 180);
  servoPlate1.attach(PLATE_SERVO1, 0, 180);
  servoPlate2.attach(PLATE_SERVO2, 0, 180);

  //Connect and configure the stepper motor to its IO pins
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);
  stepperHeight.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);
  stepperHeight.setStepsPerMillimeter(25 * 2);    // 1x microstepping

  //Start motor shield and object for adafruit driver board
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  stepperBase->setSpeed(80);  // 80 rpm (higher speeds probably won't have an effect)


  // set position of arm so it doesn't hit anything first
  servoFinger.write(OPEN);
  servoWrist.write(UP);
  setLinearActuator(1); //Up
  setPlate(0); //Back


  //-------------------------------------
  Serial.println("done with setup");

}



void loop()
{

  // This allows manual control over arm using the Serial Monitor and the keyboard
  if (Serial.available() > 0) {
    // read incoming serial data:
    char inChar = Serial.read();
    switch (inChar) {

      //----Serial Commands----

      case '9': //automatic procedure
        automaticInstructions(); 
        break;

      case 'a': //rotates arm counter-clockwise
        setRotation(rotationCurrent + stepSize);
        break;

      case 'd': //rotates arm clockwise
        setRotation(rotationCurrent - stepSize);
        break;

      case 'c': //closes gripper
        Serial.println("received: Close");
        servoFinger.write(CLOSE);
        break;

      case 'o': //opens gripper
        Serial.println("received: Open");
        servoFinger.write(OPEN);
        break;

      case 's': //moves hight up
        heightCurrent = heightCurrent + 5;
        setHeight(heightCurrent);
        break;

      case 'w': //moves height down
        heightCurrent = heightCurrent - 5;
        setHeight(heightCurrent);
        break;

      case 'q': //rotates wrist up
        Serial.println("received: Wrist up");
        servoWrist.write(UP);
        break;

      case 'e': //rotates wrist down
        Serial.println("received: Wrist down");
        servoWrist.write(DOWN);
        break;

      case 'h': //does a homing prodedure
        setHome();
        homeRotation();
        break;

      case 'j': //turns mixer on
        Serial.println("received: Mixer ON");
        digitalWrite(MIXER_PIN, MIX_ON);
        break;

      case 'k': //turns mixer off
        Serial.println("received: Mixer OFF");
        digitalWrite(MIXER_PIN, MIX_OFF);
        break;

      case 'f': //moves plate forward
        setPlate(1);  //Forward
        break;

      case 'b': //moves plate back
        setPlate(0); //Back
        break;

      case 'x': //moves the extruder up
        setLinearActuator(1); //UP
        break;

      case 'z': //moves the extruder down
        setLinearActuator(0); //DOWN
        break;



      //----Automated Heights (not really needed anymore)----

      case '1': //Home the height
        Serial.println("received: 1");
        setHome();
        heightCurrent = 0;
        break;

      case '2':
        Serial.println("received: 2"); //Train
        //heightCurrent = 275;
        setHeight(275); // drops arm down
        break;

      case '3':
        Serial.println("received: 3"); //Swing over train
        //heightCurrent = 160;
        setHeight(160); // drops arm down
        break;

      case '4':
        Serial.println("received: 4");  //Mixer height
        //heightCurrent = 30;
        setHeight(30); // drops arm down
        break;

      case '5':
        Serial.println("received: 5"); //Pusher
        setHeight(255); // drops arm down
        break;

      default:
        //Serial.println("Not a valid command");
        break;
    }
  }
}
