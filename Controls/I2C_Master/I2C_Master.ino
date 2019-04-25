// I2C Master

#include <Wire.h> // Include the required Wire library for I2C

#define CURVED 0
#define STRAIGHT 1
#define DISPENSER_SLAVE 1
#define TRAIN_SLAVE 2
#define ARM_SLAVE 3
#define MIX_FORM_SLAVE 4
#define NUMBER_OF_BAYS 11 // Don't worry about zero-based numbering, simply input normal number of bays and update quantity array
#define LOCATION_BAY1 50 // Distance from ultrasonic sensor to dispenser (units in cm [will be converted to voltage])
#define LOCATION_BAY2 50 // Try to automate this more somehow (strech goal)
#define LOCATION_BAY3 100
#define LOCATION_BAY4 100
#define LOCATION_BAY5 200
#define LOCATION_BAY6 200
#define LOCATION_BAY7 100
#define LOCATION_BAY8 100
#define LOCATION_BAY9 50
#define LOCATION_BAY10 50
#define LOCATION_BAY11 10
const int LOCATION[] = {LOCATION_BAY1,
                        LOCATION_BAY2,
                        LOCATION_BAY3,
                        LOCATION_BAY4,
                        LOCATION_BAY5,
                        LOCATION_BAY6,
                        LOCATION_BAY7,
                        LOCATION_BAY8,
                        LOCATION_BAY9,
                        LOCATION_BAY10,
                        LOCATION_BAY11
                       };

boolean straight_track;
const boolean STRAIGHT_TRACK[] = {straight_track, // Bay on straight side of track
                                  straight_track,
                                  straight_track,
                                  straight_track,
                                  straight_track,
                                  !straight_track, // Bay on curved side of track
                                  !straight_track,
                                  !straight_track,
                                  !straight_track,
                                  !straight_track,
                                  !straight_track
                                 };

int amount_bay1 = 0; // NUMBER_OF_BAYS in #define section at top
int amount_bay2 = 0;
int amount_bay3 = 0;
int amount_bay4 = 0;
int amount_bay5 = 0;
int amount_bay6 = 0;
int amount_bay7 = 0;
int amount_bay8 = 0;
int amount_bay9 = 0;
int amount_bay10 = 0;
int amount_bay11 = 0;
int quantity[] = {amount_bay1, // Bay numbers indexed as shown in bay_indexing.png in folder
                  amount_bay2,
                  amount_bay3,
                  amount_bay4,
                  amount_bay5,
                  amount_bay6,
                  amount_bay7,
                  amount_bay8,
                  amount_bay9,
                  amount_bay10,
                  amount_bay11
                 };

enum {DO_NOTHING = 0,
      MOVE,
      GO_TO_ORIGIN,
      SWITCH_TRACK
     };

void instruct(int slave, byte command, byte variable = 0, byte straight = true);

void setup() {
  Wire.begin(); // Start the I2C Bus as Master
  Serial.begin(9600);
}

void loop() {
  Serial.println("Fetching recipe");
  fetchRecipe(); // Currently receives recipe via serial monitor
  delay(1000);
  Serial.println("Fetching ingredients");
  fetchIngredients();
  delay(1000);
  Serial.println("Mixing ingredients");
  mix();
  delay(1000);
  Serial.println("Forming ingredients");
  form();
  delay(1000);
  Serial.println("Baking ingredients");
  bake(); // Not our problem
  delay(1000);
}
