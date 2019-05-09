#include <Wire.h>

#define I2C_ADDRESS 0x08

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

enum Commands {NONE, CART_CONTROL, ULTRASONIC_CONTROL, CAP_CONTROL, DISPENSER_CONTROL};
enum CartControl {CART_HOLD, CART_GO_LEFT, CART_GO_RIGHT, TRACK_SWITCH_LEFT, TRACK_SWITCH_RIGHT};
enum Sensors {NO_SENSOR, U1, U2, CAP};
Sensors sensor = NO_SENSOR;
Commands command = NONE;
CartControl cartCommand = CART_HOLD;

int destination = 0;
int destinationArray[] = {0, 0};

void setup() {
  Wire.begin(I2C_ADDRESS);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  pinMode(UPower1, OUTPUT);
  pinMode(UPower2, OUTPUT);
}

void receiveEvent() {
  while (!Wire.available());
  command = Wire.read();
  Serial.println(command);
  switch (command) {
    case CART_CONTROL:
      cartCommand = Wire.read();
      break;
    case ULTRASONIC_CONTROL:
      sensor = Wire.read();
      destinationArray[0] = Wire.read();
      destinationArray[1] = Wire.read();
      destination = destinationArray[0];
      destination = (destination << 8) | destinationArray[1];
      break;
    case CAP_CONTROL:
      sensor = Wire.read();
      break;
    default:
      Serial.println("Invalid input");
      break;
  }
}

void requestEvent() {
  Serial.println(sensor);
  switch (sensor) {
    case U1:
      digitalWrite(UPower1, HIGH); // Turns ultrasonic sensor #1 on
      while (analogRead(URead1) != destination); // Reads ultrasonic sensor value until it equals the destination
      Wire.write(analogRead(URead1)); // Tells the master the location of the cart
      digitalWrite(UPower1, LOW); // Turns ultrasonic sensor #1 off
      break;
    case U2:
      digitalWrite(UPower2, HIGH); // Turns ultrasonic sensor #2 on
      while (analogRead(URead2) != destination); // Reads ultrasonic sensor value until it equals the destination
      Wire.write(analogRead(URead2)); // Tells the master the location of the cart
      digitalWrite(UPower2, LOW); // Turns ultrasonic sensor #1 off
      break;
    case CAP:
      while (!digitalRead(capSensorPin)); // Reads capacitive sensor until it's triggered
      Wire.write(digitalRead(capSensorPin)); // Tells the master that the cart is at the capacitive sensor
      break;
    default:
      Serial.println("Invalid sensor"); // For debugging
  }
}

void loop() {}
