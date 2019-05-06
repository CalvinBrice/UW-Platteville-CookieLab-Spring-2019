// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

int x = 0;
char val;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
  Serial.println("Master");
}

void loop() {
  if (Serial.available())
  { // If data is available to read,
    x = Serial.read(); // read it and store it in val
  }

  if (x != 0) {
    // on
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
  } else {
    // off
    digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
  }

  Serial.println(x);
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("x is ");        // sends five byte
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting

}



