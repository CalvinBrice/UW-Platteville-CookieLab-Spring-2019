// I2C Slave 1

#include <Wire.h>                // Include the required Wire library for I2C
#include <Servo.h>
int wait = 0;
int closedAngle = 90; //Minimum amount that the gripper can close
int pos = 0;    // variable to store the desired servo position
int currentPos = 0; // variable to store current servo position
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards

void setup() {
  pinMode (LED_BUILTIN, OUTPUT);         // Define the LED pin as Output
  Serial.begin(9600);
  Wire.begin(1);                 // Start the I2C Bus as Slave on address 1
  Wire.onReceive(receiveEvent);  // Attach a function to trigger when something is received.

  servo1.attach(9);  // attaches the servo on pin 9 to the servo object
  servo2.attach(10);  // attaches the servo on pin 9 to the servo object
}

void receiveEvent(int bytes) {
  wait = Wire.read();               // Read one character from the I2C
}

void GripperClose() {
  pos = closedAngle;

  while (pos - currentPos != 0) {
    if (pos - currentPos < 0) {
      currentPos++;
    }
    else {
      currentPos--;
    }
    delay(15);
  }

  //  for (pos = 0; pos <= closedAngle; pos += 1) { // goes from 0 degrees to 180 degrees
  //    // in steps of 1 degree
  //    servo1.write(pos);              // tell servo to go to position in variable 'pos'
  //    servo2.write(pos);              // tell servo to go to position in variable 'pos'
  //    delay(15);                      // waits 15ms for the servo to reach the position
  //  }
}

void GripperOpen() {
  pos = 0;

  while (pos - currentPos != 0) {
    if (pos - currentPos < 0) {
      currentPos++;
    }
    else {
      currentPos--;
    }
    delay(15);
  }

  //for (pos = closedAngle; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //    servo1.write(pos);              // tell servo to go to position in variable 'pos'
  //    servo2.write(pos);              // tell servo to go to position in variable 'pos'
  //    delay(15);                      // waits 15ms for the servo to reach the position
  //  }
}

void loop() {

  if (wait == 1) {
    digitalWrite(LED_BUILTIN, HIGH);     // If value received is 0 blink LED for 200 ms
    delay(wait * 1000);
    GripperClose();
    digitalWrite(LED_BUILTIN, LOW);
    delay(wait * 1000);
  }
  if (wait == 2) {
    digitalWrite(LED_BUILTIN, HIGH);     // If value received is 0 blink LED for 200 ms
    delay(wait * 1200);
    GripperOpen();
    digitalWrite(LED_BUILTIN, LOW);
    delay(wait * 1200);
  }
  wait = 0;

}
