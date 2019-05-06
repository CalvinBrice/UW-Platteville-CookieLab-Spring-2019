// I2C Master

#include <Wire.h> // Include the required Wire library for I2C

#define CURVED 0
#define STRAIGHT 1
#define NUMBER_OF_BAYS 11 // Don't worry about zero-based numbering, simply input normal number of bays and update quantity array

// Distance from ultrasonic sensor to center of cup (ADC units)
// Try to automate this more somehow (stretch goal)
#define LOCATION_BAY1 151 // Butter
#define LOCATION_BAY2 406 // Sugar
#define LOCATION_BAY3 559 // Molasses
#define LOCATION_BAY4 744 // Vanilla
#define LOCATION_BAY5 931 // Egg
#define LOCATION_BAY6 66 // Add in 2
#define LOCATION_BAY7 237 // Chocolate Chips
#define LOCATION_BAY8 387 // Salt
#define LOCATION_BAY9 690 // Baking Soda
#define LOCATION_BAY10 801 // Flour
#define LOCATION_BAY11 955 // Oatmeal

boolean straight_track;

struct Ingredients {
  int location;
  bool trackDirection;
  int quantity;
};

Ingredients ingredient[] = { // Sets default parameters for each ingredient
  // location, straight track?, quantity
  {LOCATION_BAY1,   straight_track, 0},
  {LOCATION_BAY2,   straight_track, 0},
  {LOCATION_BAY3,   straight_track, 0},
  {LOCATION_BAY4,   straight_track, 0},
  {LOCATION_BAY5,   straight_track, 0},
  {LOCATION_BAY6,  !straight_track, 0},
  {LOCATION_BAY7,  !straight_track, 0},
  {LOCATION_BAY8,  !straight_track, 0},
  {LOCATION_BAY9,  !straight_track, 0},
  {LOCATION_BAY10, !straight_track, 0},
  {LOCATION_BAY11, !straight_track, 0},
};

enum {DO_NOTHING = 0,MOVE, GO_TO_ORIGIN, SWITCH_TRACK};
enum Slaves {NO_ONE, DISPENSER, TRAIN, ARM, MIX, FORM};
enum MotorOperation {NULL_OPERATION = 2, DISPENSE = 0, MOVE_UP = 1, MOVE_DOWN = -1};
enum Sensors {NONE, ULTRASONIC1, ULTRASONIC2}; // ULTRASONIC1 is on the straight track
MotorOperation mode = NULL_OPERATION;
Sensors slave = NONE;
Sensors sensor = NONE;

void moveTrain(int slave, byte command, byte variable = 0, byte straight = true);

void setup() {
  Wire.begin(); // Start the I2C Bus as Master
  Serial.begin(9600);
}

void loop() {
  //  Serial.println("Fetching recipe");
  fetchRecipe();
  //  Serial.println("Fetching ingredients");
  fetchIngredients();
  //  Serial.println("Mixing ingredients");
  mix();
  //  Serial.println("Forming ingredients");
  form();
  //  Serial.println("Baking ingredients");
  bake(); // Not our problem
}
