#include <Wire.h>

enum TrackDirection {CURVED, STRAIGHT}; // Basically boolean with curved as false (0) and straight as true (1)

struct Ingredients {
  int location;
  bool trackDirection;
  int quantity;
};

Ingredients ingredient[] = { // Sets default parameters for each ingredient
  // location, trackDirection, quantity
  {151, STRAIGHT, 1}, // Butter
  {406, STRAIGHT, 1}, // Sugar
  {559, STRAIGHT, 1}, // Molasses
  {744, STRAIGHT, 1}, // Vanilla
  {931, STRAIGHT, 1}, // Egg
  {66,  CURVED,   1}, // Add in 2
  {237, CURVED,   1}, // Chocolate Chips
  {387, CURVED,   1}, // Salt
  {690, CURVED,   1}, // Baking Soda
  {801, CURVED,   1}, // Flour
  {955, CURVED,   1}, // Oatmeal
};

// Ultrasonic sensor on straight track
int URead1 = A0; // Pin to read ADC value for ultrasonic sensor #1 (on straight track)
int UPower1 = 11; // Pin to power the ultrasonic sensor #1
int UValue1 = 0; // Sensor reads zero when it sees nothing

// Ultrasonic sensor on curved track
int URead2 = A1; // Pin to read ADC value for ultrasonic sensor #2 (on curved track)
int UPower2 = 10; // Pin to power the ultrasonic sensor #2
int UValue2 = 0; // Sensor reads zero when it sees nothing

// Capacitive Sensor
int capSensorPin = 9; // Pin to read the capacitor sensor's value
bool isTrainAtOrigin = false; // Variable to save the capacitor sensor's value

// Switch Pin
int switchPin = 8; // Pin to write to the switch
boolean isSwitchOnRight = false; // Variable to save the switch's direction
boolean straight = isSwitchOnRight;


// Cart Control Pin
int cartDirectionPin = 2; // Pin that controls the speed and direction of train
int trackPWM = 3; // Pin that powers the track when set HIGH

enum Commands {NONE, CART_CONTROL, ULTRASONIC_CONTROL, CAP_CONTROL, SWITCH_CONTROL, DISPENSER_CONTROL};
enum CartControl {CART_HOLD, CART_GO_LEFT, CART_GO_RIGHT, TRACK_SWITCH_LEFT, TRACK_SWITCH_RIGHT};
enum Sensors {NO_SENSOR, U1, U2, CAP};
enum DispenserControl {STOP, DISPENSE, MOVE_UP, MOVE_DOWN};

byte destinationArray[] = {0, 0};

int numberOfBays = 0;
int bay = 11;
int quantities = 5;

byte train = 0x08;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  numberOfBays = sizeof(ingredient) / sizeof(ingredient[0]); // (Memory allocated to entire struct array) / (Memory allocated to a single object in struct array) so in this case: 55 / 5 = 11
}

void loop() {
  for (int i = 0; i < numberOfBays; i++) {
    if (ingredient[i].quantity == 0) continue;
    Serial.println(ingredient[i].location);
    destinationArray[0] = (ingredient[i].location >> 8) & 0xFF; // maximum int unsigned value is 256
    destinationArray[1] = ingredient[i].location & 0xFF; // Converts ingredient[i].location to a 2 byte variable array (max value is now 65,536)
    if (i != 0) {
      if (ingredient[i - 1].trackDirection != ingredient[i].trackDirection) {
        //send cart backward
        while (!readCapSensor())
          //switch track direction
          // send cart moving ?
          switchTrack(slave, ingredient[i].trackDirection);
        if (ingredient[i].trackDirection) {

          while (!readUSensor(train, ULTRASONIC_CONTROL, destinationArray, U1)); // Wait until cart is in position
        }

      }
    }
    else if (!ingredient[i].trackDirection) while (!readUSensor(train, ULTRASONIC_CONTROL, destinationArray, U2)); // Wait until cart is in position
    else Serial.println("Error in variable: trackDirection");
    Serial.println("The cart made it to the destination");
    //    while (!dispenseIngredients(train, i, ingredient[i].quantity, DISPENSE)); // Wait until done dispensing
    //    Serial.println("Finished dispensing the proper ingredient");
  }
}
