// I2C Slave 2
// Controls the cart and its position sensors

#include <Wire.h>                // Include the required Wire library for I2C
#include <SPI.h>

const byte ADDRESS = 0x00;  // Digital pot address
const int I2C_ADDRESS = 2;  // SPI address for this controller
const int CS = 10;  // Digital pot controlling pin
const int FORWARD = 69;  // Digital pot value to go forward
const int BACKWARD = 57;  // Digital pot value to go backward
const int STOP = 60;  // Digital pot value to stop
const int CAP_SENSOR = 2; // Change to whatever pin we use <<<<<<<<<<<<<<
boolean straight = true;
uint8_t variable;

enum {DO_NOTHING = 0, MOVE, GO_TO_ORIGIN, SWITCH_TRACK};
uint8_t command;

boolean isTrackStraight; // This allows the switchTrack function to only be called iff the track is changing directions
boolean isTrainAtLocation; // Sent to master to confirm that the train is at the desired location

void setup() {
  command = 0;
  pinMode(CAP_SENSOR, INPUT); // Define the capacitor sensor output pin as an input for the Arduino
  Serial.begin(9600);
  SPI.begin();
  Wire.begin(I2C_ADDRESS);  // Start the I2C Bus as Slave on addressSPI
  Wire.onReceive(receiveEvent);  // Attach a function to trigger when something is received
  Wire.onRequest(receiveRequest); // Attach a function to trigger when the master requests something from this slave
  startingLocation(); // Put train at starting location (back against the capacitive sensor)
  switchTrack(straight);  // Changes the direction of the track at the intersection
}

void receiveEvent(int howMany) {
  while (!Wire.available()) Serial.println(Wire.available());
  command = Wire.read();
  variable = Wire.read();
  straight = Wire.read();
  //  Serial.print(command);
  //  Serial.print("  ");
  //  Serial.print(variable);
  //  Serial.print("  ");
  //  Serial.println(straight);
}

void receiveRequest() { // Not sure if I need this yet
  Wire.write(isTrainAtLocation);
  Serial.println(isTrainAtLocation);
}

void loop() {
  isTrainAtLocation = false;
  switch (command) {
    case MOVE:
      findIngredient(variable, straight);
      break;
    case GO_TO_ORIGIN:
      startingLocation();
      break;
    case SWITCH_TRACK:
      switchTrack(straight);
      break;
    default:
      Serial.println("Command equals DO_NOTHING");
  }
}
