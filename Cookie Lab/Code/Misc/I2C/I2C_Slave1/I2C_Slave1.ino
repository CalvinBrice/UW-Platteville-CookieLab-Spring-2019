// I2C Slave 1

#include <Wire.h>                // Include the required Wire library for I2C
int wait = 0;

void setup() {
  pinMode (LED_BUILTIN, OUTPUT);         // Define the LED pin as Output
  Serial.begin(9600);
  Wire.begin(1);                 // Start the I2C Bus as Slave on address 1
  Wire.onReceive(receiveEvent);  // Attach a function to trigger when something is received.
}

void receiveEvent(int bytes) {
  wait = Wire.read();               // Read one character from the I2C
}

void loop() {
  if (wait == 1) {
    digitalWrite(LED_BUILTIN, HIGH);     // If value received is 0 blink LED for 200 ms
    delay(wait * 1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(wait * 1000);
  }
  if (wait == 2) {
    digitalWrite(LED_BUILTIN, HIGH);     // If value received is 0 blink LED for 200 ms
    delay(wait * 1200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(wait * 1200);
  }
  wait = 0;
}
