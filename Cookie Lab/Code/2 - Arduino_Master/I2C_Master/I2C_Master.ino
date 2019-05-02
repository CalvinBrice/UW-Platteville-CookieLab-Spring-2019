// I2C Master

#include <Wire.h> // Include the required Wire library for I2C

#define CURVED 0
#define STRAIGHT 1
#define DISPENSER_SLAVE 1
#define TRAIN_SLAVE 2
#define ARM_SLAVE 3
#define MIX_FORM_SLAVE 4
#define NUMBER_OF_BAYS 11 // Don't worry about zero-based numbering, simply input normal number of bays and update quantity array
#define LOCATION_BAY1 50 // Distance from ultrasonic sensor to dispenser (units in cm [will be converted to from voltage])
#define LOCATION_BAY2 50 // Try to automate this more somehow (stretch goal)
#define LOCATION_BAY3 100
#define LOCATION_BAY4 100
#define LOCATION_BAY5 200
#define LOCATION_BAY6 200
#define LOCATION_BAY7 100
#define LOCATION_BAY8 100
#define LOCATION_BAY9 50
#define LOCATION_BAY10 50
#define LOCATION_BAY11 10

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

enum {DO_NOTHING = 0,
      MOVE,
      GO_TO_ORIGIN,
      SWITCH_TRACK
     };

void moveTrain(int slave, byte command, byte variable = 0, byte straight = true);

void setup() {
  Wire.begin(); // Start the I2C Bus as Master
  Serial.begin(9600);
}

//void serialEvent() {
//  while (!Serial.available());
//  int leng = Serial.read();
//  while (Serial.available() < leng);
//  int buf[leng];
//  for (int i = 0; i < leng; i++) buf[i] = Serial.read();
//  Wire.beginTransmission(8);
//  Wire.write(leng);
//  for (int i = 0; i < leng; i++) Wire.write(buf[i]);
//  Wire.endTransmission();
//}

void loop() {
  while (!Serial.available());
  int leng = Serial.read();
  while (Serial.available() < leng);
  int buf[leng];
  for (int i = 0; i < leng; i++) buf[i] = Serial.read();
  Wire.beginTransmission(8);
  Wire.write(leng);
  for (int i = 0; i < leng; i++) Wire.write(buf[i]);
  Wire.endTransmission();
//  Serial.println("Fetching recipe");
  fetchRecipe(); // Currently receives recipe via serial monitor
//  Serial.println("Fetching ingredients");
  fetchIngredients();
//  Serial.println("Mixing ingredients");
  mix();
//  Serial.println("Forming ingredients");
  form();
//  Serial.println("Baking ingredients");
  bake(); // Not our problem
}
