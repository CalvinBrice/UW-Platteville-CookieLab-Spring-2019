
// zoomkat 10-22-11 serial servo test
// type servo position 0 to 180 in serial monitor
// or for writeMicroseconds, use a value like 1500
// for IDE 0022 and later
// Powering a servo from the arduino usually *DOES NOT WORK*.

String readString;
#include <Servo.h>
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo

const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data

boolean newData = false;
int n = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
  servo1.attach(9);  //the pin for the servo control
  servo2.attach(10);  //the pin for the servo control
}

void loop() {
  recvWithEndMarker();
  showNewData();
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  // if (Serial.available() > 0) {
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void showNewData() {
  if (newData == true) {
    //    Serial.print("This just in ... ");
    //    Serial.println(receivedChars);
    //    n = receivedChars.toInt();
    newData = false;
    Serial.print("writing Angle: ");
    Serial.println(receivedChars);
    servo1.write(receivedChars);
    servo2.write(receivedChars);
  }
}
