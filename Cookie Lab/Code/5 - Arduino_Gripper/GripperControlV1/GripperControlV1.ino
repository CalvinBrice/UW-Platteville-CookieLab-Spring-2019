#include <Servo.h>

const byte epinA = 2;
const byte epinB = 3;

int printInterval = 500;

volatile int encoderCount = 0;

Servo servo;

int servoPos = 0;


void setup(){

  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(epinA), eintA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(epinB), eintB, CHANGE);
  servo.attach(9);
  
}

void loop(){

  static unsigned long pt = millis();
  unsigned long ct = millis();
  
  int encoderRead = 0;

  if(ct - pt >= printInterval){
    cli();
    encoderRead = encoderCount;
    encoderCount = 0;
    sei();
    Serial.println(encoderRead);

    servoPos += encoderRead;
    servoPos = constrain(servoPos, 0, 180);

    servo.write(servoPos);    
    
  }  
  
}


void eintA(){
  // if the pins read the same we're going one direction
  // else we're going the other direction.
  if(!!(PIND & 4) == !!(PIND & 8)){
    encoderCount++;
  }
  else {
    encoderCount--;
  }
}

void eintB(){
  // Same as above, except the directions are switched for
  // the other pin.  
  if(!!(PIND & 4) == !!(PIND & 8)){
    encoderCount--;
  }
  else {
    encoderCount++;
  }
}
