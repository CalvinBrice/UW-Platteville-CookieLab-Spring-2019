#include <Wire.h>

enum Slaves {DISPENSER = 0X08, CART = 0x09, ARM = 0X10, MIXER_FORMER = 0x11};
enum Commands {NONE, CART_CONTROL, ULTRASONIC_CONTROL, CAP_CONTROL, DISPENSER_CONTROL};
enum CartControl {CART_NONE, CART_GO_TO_INDUCTOR, CART_GO_TO_ULTRASONIC, TRACK_SWITCH_CURVED, TRACK_SWITCH_STRAIGHT};
enum Sensors {NO_SENSOR, U1, U2, CAP};
enum DispenserControl {STOP, DISPENSE, MOVE_UP, MOVE_DOWN};
enum TrackDirection {STRAIGHT, CURVED}; // Basically boolean with curved as false (0) and straight as true (1)

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
  {"Sugar",           379, STRAIGHT, 1},
  {"Molasses",        534, STRAIGHT, 1},
  {"Vanilla",         721, STRAIGHT, 1},
  {"Egg",             903, STRAIGHT, 1},
  {"Add in 2",         43, CURVED,   1},
  {"Chocolate Chips", 207, CURVED,   1},
  {"Salt",            360, CURVED,   1},
  {"Baking Soda",     661, CURVED,   1},
  {"Flour",           778, CURVED,   1},
  {"Oatmeal",         927, CURVED,   1}
};

int numberOfBays = 0;

int destination = 1100;
byte destArray[] = {(destination >> 8) & 0xFF, destination & 0xFF};

void setup() {
  Wire.begin();
  Serial.begin(9600);
  numberOfBays = sizeof(ingredient) / sizeof(ingredient[0]); // (Memory allocated to entire struct array) / (Memory allocated to a single object in struct array) so in this case: 55 / 5 = 11
}

//void serialEvent() { // Doesn't seem to work properly?
//  sendCommand(CART, CART_NONE);
//  delay(100000);
//}

void loop() {
  // For now I'm assuming the cart is at the inductive sensor
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
  while (!serialWait()); // Robot arm code takes over here
}
