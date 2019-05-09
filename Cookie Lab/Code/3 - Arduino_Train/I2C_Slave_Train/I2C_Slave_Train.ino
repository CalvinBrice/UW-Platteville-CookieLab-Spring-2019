// I2C Slave 0x09
// Controls the cart and its position sensors

#include <Wire.h> // Include the required Wire library for I2C

#define I2C_ADDRESS 0x09

uint8_t destination;

enum Commands {DO_NOTHING = 0, MOVE, GO_TO_ORIGIN, SWITCH_TRACK};
enum Sensors {NONE, ULTRASONIC1, ULTRASONIC2, CAP_SENSOR}; // ULTRASONIC1 is on the straight track
enum Speeds {STOP = 0, SLOW = 50, FAST = 100}; // BACKWARD and FORWARD are reserved
Commands command = DO_NOTHING;
Sensors sensor = NONE;
//Speeds trainSpeed = STOP;

boolean isTrainAtLocation; // Sent to master to confirm that the train is at the desired location

// Ultrasonic sensor on straight track
int ultrasonicRead1 = A0; // Pin to read ADC value for ultrasonic sensor #1 (on straight track)
int ultrasonicPower1 = 11; // Pin to power the ultrasonic sensor #1
int ultrasonicValue1 = 0; // Sensor reads zero when it sees nothing

// Ultrasonic sensor on curved track
int ultrasonicRead2 = A1; // Pin to read ADC value for ultrasonic sensor #2 (on curved track)
int ultrasonicPower2 = 10; // Pin to power the ultrasonic sensor #2
int ultrasonicValue2 = 0; // Sensor reads zero when it sees nothing

// Capacitive Sensor
int capSensorPin = 12; // Pin to read the capacitor sensor's value
bool isTrainAtOrigin = false; // Variable to save the capacitor sensor's value

// Switch Pin
int switchPin = 8; // Pin to write to the switch
boolean isSwitchOnRight = false; // Variable to save the switch's direction
boolean straight = isSwitchOnRight;

// Cart Control Pin
int cartDirectionPin = 2; // Pin that controls the speed and direction of train
int trackPWM = 3; // Pin that powers the track when set HIGH

void setup() {
  Serial.begin(9600); // Starts the communication from the arduino to the serial line (See serial monitor)
  Wire.begin(I2C_ADDRESS);  // Start the I2C Bus as Slave on addressSPI
  Wire.onReceive(receiveEvent);  // Attach a function to trigger when something is received
  Wire.onRequest(receiveRequest); // Attach a function to trigger when the master requests something from this slave
  analogWrite(cartDirectionPin, STOP);
  goingToOrigin(); // Put train at starting location (back against the capacitive sensor)
  switchTrack(straight);  // Changes the direction of the track at the intersection
  pinMode(ultrasonicPower1, OUTPUT); // Initialization of ultrasonic sensor #1
  pinMode(ultrasonicPower2, OUTPUT); // Initialization of ultrasonic sensor #2
  pinMode(switchPin, OUTPUT); // Initialization of switch
  pinMode(capSensorPin, INPUT); // Initialization of capacitive sensor
  pinMode(cartDirectionPin, OUTPUT); // Initilization of cart's controlling pin
}

void receiveEvent(int howMany) {
  if (howMany > 1) {
    while (!Wire.available()) Serial.println(Wire.available());
    command = Wire.read();
    destination = Wire.read();
    straight = Wire.read();
  }
  else if (howMany == 1) sensor = Wire.read();
}

void receiveRequest() {
  switch (sensor) {
    case ULTRASONIC1:
      Wire.write(ultrasonicValue1);
      break;
    case ULTRASONIC2:
      Wire.write(ultrasonicValue2);
      break;
    case CAP_SENSOR:
      Wire.write(isTrainAtOrigin);
      break;
    case NONE:
      Serial.println("No sensor selected"); // thisSensor = NONE
      break;
    default:
      Serial.println("Error selecting sensor"); // thisSensor is not equal to Sensors enum
      break;
  }
}

void loop() {
  switch (command) {
    case MOVE:
      if (straight) sensor = ULTRASONIC1;
      else if (!straight) sensor = ULTRASONIC2;
      findIngredient(destination, sensor);
      break;
    case GO_TO_ORIGIN:
      goingToOrigin();
      break;
    case SWITCH_TRACK:
      switchTrack(straight);
      break;
    case DO_NOTHING:
      Serial.println("No action required");
      break;
    default:
      Serial.println("Error selecting command"); // command is not equal to Commands enum
      break;
  }
}
