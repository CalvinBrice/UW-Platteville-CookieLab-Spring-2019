#include <Wire.h>
#include <Adafruit_MotorShield.h>

#define STEPS_PER_REV 200

int Steps;
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

enum Slaves {MASTER = 0x08, CART = 0x09, ARM = 0X10};
enum Commands {NONE, CART_CONTROL, ULTRASONIC_CONTROL, CAP_CONTROL, DISPENSER_CONTROL};
enum CartControl {CART_NONE, CART_GO_TO_INDUCTOR, CART_GO_TO_ULTRASONIC, TRACK_SWITCH_CURVED, TRACK_SWITCH_STRAIGHT};
enum Sensors {NO_SENSOR, U1, U2, CAP};
enum DispenserControl {STOP, DISPENSE, MOVE_UP, MOVE_DOWN};
enum TrackDirection {STRAIGHT, CURVED}; // Basically boolean with curved as false (0) and straight as true (1)
DispenserControl mode = STOP;

Slaves slave = CART;
Commands command = NONE;

struct Ingredients {
  String label;
  int location;
  int trackDirection;
  int quantity;
};

Ingredients ingredient[] = { // Sets default parameters for each ingredient
  // label, location, trackDirection, quantity
  {"Butter",          126, STRAIGHT, 0},
  {"Sugar",           379, STRAIGHT, 0},
  {"Molasses",        534, STRAIGHT, 0},
  {"Vanilla",         721, STRAIGHT, 0},
  {"Egg",             903, STRAIGHT, 0},
  {"Add in 2",         43, CURVED,   0},
  {"Chocolate Chips", 207, CURVED,   0},
  {"Salt",            360, CURVED,   0},
  {"Baking Soda",     661, CURVED,   0},
  {"Flour",           778, CURVED,   0},
  {"Oatmeal",         927, CURVED,   0}
};

int destination = 1100;
byte destArray[] = {(destination >> 8) & 0xFF, destination & 0xFF};

bool armInControl = false;

void setup() {
  Wire.begin(MASTER);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  setupMotors();
  //  numberOfBays = sizeof(ingredient) / sizeof(ingredient[0]); // (Memory allocated to entire struct array) / (Memory allocated to a single object in struct array) so in this case: 55 / 5 = 11
}

//void serialEvent() { // Doesn't seem to work properly?
//  sendCommand(CART, CART_NONE);
//  delay(100000);
//}

void loop() {
  // For now I'm assuming the cart is at the inductive sensor
  while (!Serial.available());
  int numberOfBays = Serial.read();
  Serial.println(numberOfBays);
  for (int i = 0; i < numberOfBays; i++) blinker(Serial.read());
  while (armInControl);
  for (int i = 0; i < numberOfBays; i++) {
    if (ingredient[i].quantity == 0) continue; // Ignore null ingredient quantities
    if (i != 0 && ingredient[i].trackDirection != ingredient[i - 1].trackDirection) { // Checks to see if the cart needs to switch branches
      sendCommand(CART, CART_GO_TO_INDUCTOR); // Start of the "switching branches" sequence
      while (!requestCapacitanceFromSlave());
      if (ingredient[i].trackDirection) sendCommand(CART, TRACK_SWITCH_STRAIGHT);
      if (!ingredient[i].trackDirection) sendCommand(CART, TRACK_SWITCH_CURVED);
    } // End of the "switching branches" sequence
    if (!ingredient[i].trackDirection) sendCommand(CART, TRACK_SWITCH_STRAIGHT);
    if (ingredient[i].trackDirection) sendCommand(CART, TRACK_SWITCH_CURVED);
    sendCommand(CART, CART_GO_TO_ULTRASONIC);
    while (!readUSensor(CART, ULTRASONIC_CONTROL, ingredient[i].location, ingredient[i].trackDirection));
    while (!doneDispensing(i, ingredient[i].quantity));
  }
  sendCommand(CART, CART_GO_TO_INDUCTOR);
  while (!requestCapacitanceFromSlave());
  while (!serialWait()); // Used for testing arm and master arduinos
  giveArmControl();
  armInControl = true;
}
