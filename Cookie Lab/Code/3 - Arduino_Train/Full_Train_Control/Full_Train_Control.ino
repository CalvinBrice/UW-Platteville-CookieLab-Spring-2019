#include <Wire.h>

// Ultrasonic sensor on straight track
int URead1 = A0; // Pin to read ADC value for ultrasonic sensor #1 (on straight track)
int UPower1 = 11; // Pin to power the ultrasonic sensor #1

// Ultrasonic sensor on curved track
int URead2 = A1; // Pin to read ADC value for ultrasonic sensor #2 (on curved track)
int UPower2 = 10; // Pin to power the ultrasonic sensor #2

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

enum Slaves {DISPENSER = 0X08, TRAIN = 0x09, ARM = 0X10};
enum Commands {NONE, CART_CONTROL, ULTRASONIC_CONTROL, CAP_CONTROL, DISPENSER_CONTROL};
enum CartControl {CART_NONE, CART_GO_TO_INDUCTOR, CART_GO_TO_ULTRASONIC, TRACK_SWITCH_CURVED, TRACK_SWITCH_STRAIGHT};
enum CartSpeed {CART_STOP = 0, CART_GO = 255};
enum Sensors {NO_SENSOR, U1, U2, CAP};
enum DispenserControl {STOP, DISPENSE, MOVE_UP, MOVE_DOWN};

Commands controlCommand = NONE;
CartControl cartCommand = CART_NONE;
Sensors sensor = NO_SENSOR;

int destination = 0;

void setup() {
  Wire.begin(TRAIN);
  analogWrite(trackPWM, CART_STOP);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);
  pinMode(cartDirectionPin, OUTPUT);
  pinMode(switchPin, OUTPUT);
  pinMode(capSensorPin, INPUT);
  pinMode(UPower1, OUTPUT);
  pinMode(UPower2, OUTPUT);
  digitalWrite(UPower1, LOW);
  digitalWrite(UPower2, LOW);
  digitalWrite(switchPin, LOW); // Set track to straight
  digitalWrite(cartDirectionPin, LOW); // Set direction to right

  // Find the cart and set it to the inductive sensor
  setCartToOrigin();
}

void receiveEvent() {
  while (!Wire.available());
  controlCommand = Wire.read();
  if (controlCommand == CART_CONTROL) cartCommand = Wire.read();
  else if (controlCommand == ULTRASONIC_CONTROL) {
    sensor = Wire.read();
    destination = Wire.read();
    destination = (destination << 8) | Wire.read();
  }
  else if (controlCommand == CAP_CONTROL) sensor = CAP;
  else Serial.println("Invalid input");
}

void requestEvent() {
  int UValue = 0;
  switch (sensor) {
    case U1:
      digitalWrite(UPower1, HIGH);
      UValue = analogRead(URead1);
      while (UValue < destination) UValue = analogRead(URead1);
      cartCommand = CART_NONE;
//      Serial.println(UValue);
      Wire.write(UValue);
      digitalWrite(UPower1, LOW);
      break;
    case U2:
      digitalWrite(UPower2, HIGH);
      UValue = analogRead(URead2);
      while (UValue < destination) UValue = analogRead(URead2);
      cartCommand = CART_NONE;
      Wire.write(UValue);
      digitalWrite(UPower2, LOW);
      break;
    case CAP:
      while (!digitalRead(capSensorPin));
      Wire.write(digitalRead(capSensorPin));
      cartCommand = CART_NONE;
      break;
    default:
      Serial.print("Invalid sensor: ");
      Serial.println(sensor);
      cartCommand = CART_NONE;
      break;
  }
}

void loop() {
  switch (cartCommand) {
    case CART_NONE:
      analogWrite(trackPWM, CART_STOP);
      break;
    case CART_GO_TO_ULTRASONIC:
      digitalWrite(cartDirectionPin, HIGH);
      analogWrite(trackPWM, CART_GO);
      break;
    case CART_GO_TO_INDUCTOR:
      digitalWrite(cartDirectionPin, LOW);
      analogWrite(trackPWM, CART_GO);
      break;
    case TRACK_SWITCH_CURVED:
      digitalWrite(switchPin, HIGH);
      break;
    case TRACK_SWITCH_STRAIGHT:
      digitalWrite(switchPin, LOW);
      break;
    default:
      Serial.print("Invalid command: ");
      Serial.println(controlCommand);
      break;
  }
}
