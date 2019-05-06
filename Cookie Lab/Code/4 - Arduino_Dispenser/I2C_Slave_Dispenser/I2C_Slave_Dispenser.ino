// I2C Slave 1
// Controls the entire dispenser

#include <Wire.h> // Include the required Wire library for I2C
#include <Adafruit_MotorShield.h>

#define I2C_SLAVE_ADDRESS 1
#define STEPS_PER_REV 200

int bay = 0;
int quantity = 0;
enum MOTOR_OPERATION {NONE = 2, DISPENSE = 0, MOVE_UP = 1, MOVE_DOWN = -1};
MOTOR_OPERATION mode = NONE;

int Steps;
float Step2;
int Jog = 20; //defines the step "length" of the jog button
int ButterJog = 5000;
int BakingSodaJog = 5;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS_0 = Adafruit_MotorShield(0x60); // default board ID
Adafruit_MotorShield AFMS_1 = Adafruit_MotorShield(0x61); // board ID + 1
Adafruit_MotorShield AFMS_2 = Adafruit_MotorShield(0x62); // board ID + 2
Adafruit_MotorShield AFMS_3 = Adafruit_MotorShield(0x63); // board ID + 3
Adafruit_MotorShield AFMS_4 = Adafruit_MotorShield(0x64); // board ID + 4
Adafruit_MotorShield AFMS_5 = Adafruit_MotorShield(0x65); // board ID + 5

// Connect a stepper motors with 200 steps per revolution (1.8 degree)
Adafruit_StepperMotor *myMotor1 = AFMS_0.getStepper(STEPS_PER_REV, 1); //   Butter
Adafruit_StepperMotor *myMotor2 = AFMS_0.getStepper(STEPS_PER_REV, 2); //   Vanilla
Adafruit_StepperMotor *myMotor3 = AFMS_1.getStepper(STEPS_PER_REV, 1); //   Molasses
Adafruit_StepperMotor *myMotor4 = AFMS_1.getStepper(STEPS_PER_REV, 2); //   Egg
Adafruit_StepperMotor *myMotor5 = AFMS_2.getStepper(STEPS_PER_REV, 1); //   Sugar
Adafruit_StepperMotor *myMotor6 = AFMS_2.getStepper(STEPS_PER_REV, 2); //   Baking soda
Adafruit_StepperMotor *myMotor7 = AFMS_3.getStepper(STEPS_PER_REV, 1); //   Chocolate chips
Adafruit_StepperMotor *myMotor8 = AFMS_3.getStepper(STEPS_PER_REV, 2); //   Oats
Adafruit_StepperMotor *myMotor9 = AFMS_4.getStepper(STEPS_PER_REV, 1); //   Flour
Adafruit_StepperMotor *myMotor10 = AFMS_4.getStepper(STEPS_PER_REV, 2); //  Salt
Adafruit_StepperMotor *myMotor11 = AFMS_5.getStepper(STEPS_PER_REV, 1); //  M&M's
Adafruit_DCMotor *myMotor12 = AFMS_5.getMotor(3); //  dc motor relay for flour agitator using port 3 (M3)

void setup() {
  setupMotors();
  Serial.begin(9600);
  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);  // Attach a function to trigger when something is received.
}

void receiveEvent(int howMany) {
  while (!Wire.available());       // Wait for a byte to show up on the wire
  bay = Wire.read();               // Read first byte from the I2C_Master
  quantity = Wire.read();          // Read second byte from the I2C_Master
  mode = Wire.read();              // Read third byte from the I2C_Master
  Serial.println("Bay: " + String(bay) + " | " + "Quantity: " + String(quantity) + " | " + "Mode: " + String(mode));
}

void loop() {
  switch (bay) {
    case 1:
      butter();
      break;
    case 2:
      sugar();
      break;
    case 3:
      molasses();
      break;
    case 4:
      vanilla();
      break;
    case 5:
      egg();
      break;
    case 6:
      mms();
      break;
    case 7:
      chocolateChips();
      break;
    case 8:
      salt();
      break;
    case 9:
      bakingSoda();
      break;
    case 10:
      flour();
      break;
    case 11:
      oats();
      break;
    default:
      break;
  }
}
