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

#include <SpeedyStepper.h> //Library for linear actuator
#include <Adafruit_MotorShield.h> //Library for base rotation stepper
#include <Servo.h>
#include <Wire.h>

#define I2C_ADDRESS 0x10 //(update)

// pin assignments
int LED_PIN = 13;
int MOTOR_STEP_PIN = 6;       // --> PUL+
int MOTOR_DIRECTION_PIN = 4;  // --> DIR+
int LIMIT_SWITCH_PIN = 8;     // --> Limit switch RED wire
int FINGER_SERVO = 9;
int WRIST_SERVO = 10;

// setup physical objects
Servo servoFinger;  // create servo object to control a servo
Servo servoWrist;  // create servo object to control a servo
SpeedyStepper stepperHeight; // create the stepper motor object
Adafruit_MotorShield AFMS = Adafruit_MotorShield();  // Create the motor shield object with the I2C address
Adafruit_StepperMotor *stepperBase = AFMS.getStepper(400, 2); // Connect a stepper motor with 200 steps per revolution (1.8 degree) to motor port #2 (M3 and M4)

// Structs
typedef struct {
  float pos;
  float cur;
  float minimum;
  float maximum;
} arm;

//arm "name" = {pos, cur, minimum, maximum};
arm finger = {0, 0, 0, 180};    //initializes a finger under the arm type with (pos, cur, minimum, maximum)
arm wrist = {0, 0, 6, 107};     //wrist is limited by wiring length... do not mess with these values or you risk damage
arm height = {0, 0, 0, 370};    //maximum travel of linear actuator is 400mm - the height of the limit switch (30mm)
arm rotation = {0, 0, 0, 180};  //needs to be updated

enum Finger {OPEN, CLOSE};
enum Wrist {UP, DOWN};
Finger finger = OPEN;
Wrist wrist = UP;

void setup()
{
  Serial.begin(9600);
  Serial.println("Robotic Arm Arduino");

  Wire.begin(I2C_ADDRESS);  // Start the I2C Bus as Slave on addressSPI
  Wire.onReceive(receiveEvent);  // Attach a function to trigger when something is received
  Wire.onRequest(receiveRequest); // Attach a function to trigger when the master requests something from this slave

  pinMode(LED_PIN, OUTPUT);
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

  //Initialize servos
  servoFinger.attach(FINGER_SERVO);   // attaches the servo on specified pin to the servo object
  servoWrist.attach(WRIST_SERVO);    // attaches the servo on specified pin to the servo object

  // connect and configure the stepper motor to its IO pins with external driver
  stepperHeight.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);
  stepperHeight.setStepsPerMillimeter(25 * 2);    // 1x microstepping

  // connect and configure the stepper motor to its IO pins with Adafruit shield
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  stepperBase->setSpeed(80);  // 10 rpm

  //----------------------------------------
  // Automation

  // set position of arm so it doesn't hit anything first
  servoFinger.write(180); //open fingers
  servoWrist.write(6);    //default horizontal

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

void receiveEvent(String Commands) {
  switch (Commands) {
    case FINGERS_OPEN:

      break;
    case FINGERS_CLOSE:
      //      goingToOrigin();
      break;
    case WRIST_UP:
      Serial.println("Wrist uo");
      servoWrist.write(wrist.minimum);
      break;
    case WRIST_DOWN:
      Serial.println("Wrist down");
      servoWrist.write(wrist.maximum);
      break;
    default:
      Serial.println("Error selecting command"); // command is not equal to Commands enum
      break;
  }
}
