/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
int closedAngle = 100;

Servo servo1;  // create servo object to control a servo 
Servo servo2;  // create servo object to control a servo 
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  servo1.attach(9);  // attaches the servo on pin 9 to the servo object
  servo2.attach(10);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = 0; pos <= closedAngle; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo1.write(pos);              // tell servo to go to position in variable 'pos'
    servo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(5000);
  for (pos = closedAngle; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo1.write(pos);              // tell servo to go to position in variable 'pos'
    servo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(5000);


//servo1.write(0);              // tell servo to go to position in variable 'pos'
//servo2.write(0);              // tell servo to go to position in variable 'pos'
//delay(15);                       // waits 15ms for the servo to reach the position
}
