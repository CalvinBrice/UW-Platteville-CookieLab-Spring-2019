//----------------------------------------------------------------------------------
//  Name: Fully Automated Gripper Code
//
//  Repository: https://github.com/CalvinBrice/UW-Platteville-CookieLab-Spring-2019-
//
//  Author(s): Calvin Brice, Austen Owens
//  Date: 5/7/2019
//
//  Notes:
//  This should be automated so that a sequence of positional values may be transmitted via
//  i2c and translated into movements of the gripper, wrist, linear actuator, and base rotation
//
//  *Fix delay with millis
//----------------------------------------------------------------------------------

// --- Import correct libraries ---
#include <SpeedyStepper.h> //Library for linear actuator
#include <Adafruit_MotorShield.h> //Library for base rotation stepper
#include <Servo.h>
#include <Wire.h>

bool debug = true;             // enables serial debugging
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
Adafruit_MotorShield AFMS = Adafruit_MotorShield();  // 0x66 Create the motor shield object with the I2C address (verify it isn't used by other shields for dispenser)
Adafruit_StepperMotor *stepperBase = AFMS.getStepper(400, 2); // Connect a stepper motor with 400 steps per revolution (1.8 degree) to motor port #2 (M3 and M4)



// --- servo input parameters... ---
enum GRIP {OPEN = 180, CLOSE = 25};
enum WRIST {UP = 12, DOWN = 165};
enum MIXER {MIX_ON = HIGH, MIX_OFF = LOW};
GRIP gripper = OPEN;  // declares object of gripper and sets initial position
WRIST wrist = UP;     // declares object of wrist and sets initial position
MIXER mixer = MIX_OFF;    // declares object of mixer and sets initial state


// --- replaces delay() because that causes issues ---

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
  Serial.println("Gripper Arduino");
  pinMode(LED_PIN, OUTPUT);

  //i2c initialization
  Wire.begin(MY_ADDRESS); // join i2c bus with address
  Wire.onReceive(receiveEvent); // register event

  //Set relay pin for mixer
  pinMode(MIXER_PIN, OUTPUT);

  //Set relay pin for linear actuator
  pinMode(LINEAR_ACTUATOR_UP, OUTPUT);
  pinMode(LINEAR_ACTUATOR_DOWN, OUTPUT);

  //Initialize servos
  servoFinger.attach(FINGER_SERVO, 0 , 180);  // attaches the servo on specified pin to the servo object
  servoWrist.attach(WRIST_SERVO, 0, 180);
  servoPlate1.attach(PLATE_SERVO1, 0, 180);
  servoPlate2.attach(PLATE_SERVO2, 0, 180);

  // connect and configure the stepper motor to its IO pins
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);
  stepperHeight.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);
  stepperHeight.setStepsPerMillimeter(25 * 2);    // 1x microstepping

  //Start motor shield and object for adafruit
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  stepperBase->setSpeed(80);  // 80 rpm

  // set position of arm so it doesn't hit anything first
  servoFinger.write(OPEN);
  servoWrist.write(UP);
  setLinearActuator(1); //Up
  setPlate(0);          //Back



  //-------------------------------------
  Serial.println("done with setup");

}



void loop()
{
  if (Serial.available() > 0) {
    // read incoming serial data:
    char inChar = Serial.read();
    switch (inChar) {
      //----Commands----
      case 'a':
        setRotation(rotationCurrent + stepSize);
        break;

      case 'd':
        setRotation(rotationCurrent - stepSize);
        break;

      case 'c':
        Serial.println("received: Close");
        servoFinger.write(CLOSE);
        break;

      case 'o':
        Serial.println("received: Open");
        servoFinger.write(OPEN);
        break;

      case 's':
        Serial.println("received: Down");
        heightCurrent = heightCurrent + 5;
        setHeight(heightCurrent);
        Serial.print("moving to height: ");
        Serial.println(heightCurrent);
        break;

      case 'w':
        Serial.println("received: Up");
        heightCurrent = heightCurrent - 5;
        setHeight(heightCurrent);
        Serial.print("moving to height: ");
        Serial.println(heightCurrent);
        break;

      case 'q':
        Serial.println("received: wrist up");
        servoWrist.write(UP);
        break;

      case 'e':
        Serial.println("received: wrist down");
        servoWrist.write(DOWN);
        break;

      case 'h':
        setHome();
        homeRotation();
        break;

      case 'j':
        Serial.println("received: Mixer on");
        digitalWrite(MIXER_PIN, MIX_ON);
        break;

      case 'k':
        Serial.println("received: Mixer off");
        digitalWrite(MIXER_PIN, MIX_OFF);
        break;

      case 'f':
        setPlate(1);  //Forward
        break;

      case 'b':
        setPlate(0); //Back
        break;

      case 'x':
        setLinearActuator(1); //UP
        break;


      case 'z':
        setLinearActuator(0); //DOWN
        break;

      case '0':
        automaticInstructions(); //automatic procedure
        break;


      //----Automated Heights----

      case '1':
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
