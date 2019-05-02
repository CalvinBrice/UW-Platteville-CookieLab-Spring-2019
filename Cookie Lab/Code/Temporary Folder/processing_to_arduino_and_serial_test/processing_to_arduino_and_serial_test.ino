#include <Wire.h>

int leng = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int howMany) {
  while (!Wire.available());
  leng = Wire.read();
  Serial.println(leng);
  for (int i = 0; i < leng; i++) {
    Serial.print(String(i+1)+": ");
    Serial.println(Wire.read());
  }
}

void loop() {}

void types(String a) {
  Serial.println("it's a String");
}
void types(int a)   {
  Serial.println("it's an int");
}
void types(char* a) {
  Serial.println("it's a char*");
}
void types(float a) {
  Serial.println("it's a float");
}
void types(byte a) {
  Serial.println("it's a byte");
}
