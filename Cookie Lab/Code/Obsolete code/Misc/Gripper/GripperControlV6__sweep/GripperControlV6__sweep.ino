/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
int pos = 0;    // variable to store the servo position
int currentPos = 0; // variable to store current servo position
int closedAngle = 90;

Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards

void setup() {
  Serial.begin(9600);
  servo1.attach(9);  // attaches the servo on pin 9 to the servo object
  servo2.attach(10);  // attaches the servo on pin 9 to the servo object
}

void GripperClose() {
  pos = closedAngle;
  Serial.println("Gripper Close:");
  Serial.print("pos =  ");
  Serial.print(pos);
  Serial.print(" | currentPos =  ");
  Serial.println(currentPos);

  while (pos - currentPos != 0) {
    if (pos - currentPos > 0) {
      currentPos++;
    }
    else {
      currentPos--;
    }
    Serial.print("pos =  ");
    Serial.print(pos);
    Serial.print(" | currentPos =  ");
    Serial.println(currentPos);
    servo1.write(currentPos);              // tell servo to go to position in variable 'pos'
    servo2.write(currentPos);              // tell servo to go to position in variable 'pos'
    delay(15);
  }
}

void GripperOpen() {
  pos = 0;
  Serial.println("Gripper Open:");
  Serial.print("pos =  ");
  Serial.print(pos);
  Serial.print(" | currentPos =  ");
  Serial.println(currentPos);

  while (pos - currentPos != 0) {
    if (pos - currentPos > 0) {
      currentPos++;
    }
    else {
      currentPos--;
    }
    Serial.print("pos =  ");
    Serial.print(pos);
    Serial.print(" | currentPos =  ");
    Serial.println(currentPos);
    servo1.write(currentPos);              // tell servo to go to position in variable 'pos'
    servo2.write(currentPos);              // tell servo to go to position in variable 'pos'
    delay(15);
  }
}

void waitfunc(int sec) {
  for (int i = 1; i <= sec; i++) {
    Serial.print("wait... | ");
    Serial.println (i);
    delay(1000);
  }
}

void loop() {
  GripperOpen();
  waitfunc(5); // Wait 10 sec
  GripperClose();
  waitfunc(5); // Wait 10 sec
}
