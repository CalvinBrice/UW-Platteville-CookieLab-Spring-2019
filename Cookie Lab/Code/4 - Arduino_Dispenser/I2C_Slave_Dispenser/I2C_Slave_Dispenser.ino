// I2C Slave 1
// Controls the entire dispenser

#include <Wire.h>                // Include the required Wire library for I2C
int bay = 0;

void setup() {
  pinMode (LED_BUILTIN, OUTPUT);         // Define the LED pin as Output
  Serial.begin(9600);
  Wire.begin(1);                 // Start the I2C Bus as Slave on address 1
  Wire.onReceive(receiveEvent);  // Attach a function to trigger when something is received.
}

void receiveEvent(int bytes) {
  bay = Wire.read();               // Read first character from the I2C_Master
}

void loop() {
  // dispense <quantity> at <bay> ingredient dispenser
  bay = 0;
}
