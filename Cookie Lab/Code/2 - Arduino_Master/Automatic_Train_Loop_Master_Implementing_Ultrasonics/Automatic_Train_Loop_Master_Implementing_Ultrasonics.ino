#include <Wire.h>

enum Positions {BASE, TOP_STRAIGHT, TOP_CURVED};
enum Slaves {DISPENSER = 0X08, TRAIN = 0x09, ARM = 0X10, MIXER_FORMER = 0x11};
enum Commands {NONE, CART_CONTROL, ULTRASONIC_CONTROL, CAP_CONTROL, DISPENSER_CONTROL};
enum CartControl {CART_HOLD, CART_GO_LEFT, CART_GO_RIGHT, TRACK_SWITCH_CURVED, TRACK_SWITCH_STRAIGHT};
enum Sensors {NO_SENSOR, U1, U2, CAP};
enum DispenserControl {STOP, DISPENSE, MOVE_UP, MOVE_DOWN};

Positions trainPosition = BASE;
Positions pastPosition = TOP_CURVED;
Slaves slave = TRAIN;
Commands command = NONE;

bool capSensorTriggered = false;
bool endOfTheLine = false;

int destination = 1100;
byte destArray[] = {(destination >> 8) & 0xFF, destination & 0xFF};

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void serialEvent() { // Doesn't seem to work properly?
  sendCommand(TRAIN, STOP);
  delay(100000);
}

void loop() {
  switch (trainPosition) {
    case BASE:
      if (pastPosition == TOP_STRAIGHT) {
        pastPosition = BASE;
        sendCommand(TRAIN, TRACK_SWITCH_CURVED);
        sendCommand(TRAIN, CART_GO_LEFT);
        while (!readUSensor(TRAIN, ULTRASONIC_CONTROL, 950, U1));
        trainPosition = TOP_CURVED;
        endOfTheLine = false;
      }
      else if (pastPosition == TOP_CURVED) {
        pastPosition = BASE;
        sendCommand(TRAIN, TRACK_SWITCH_STRAIGHT);
        sendCommand(TRAIN, CART_GO_LEFT);
        while (!readUSensor(TRAIN, ULTRASONIC_CONTROL, 950, U2));
        trainPosition = TOP_STRAIGHT;
        endOfTheLine = false;
      }
      else Serial.println("Train was and is at the base of the track.");
      break;
    case TOP_STRAIGHT:
      pastPosition = TOP_STRAIGHT;
      sendCommand(TRAIN, CART_GO_RIGHT);
      requestCapacitanceFromSlave(CAP);
      trainPosition = BASE;
      break;
    case TOP_CURVED:
      pastPosition = TOP_CURVED;
      sendCommand(TRAIN, CART_GO_RIGHT);
      requestCapacitanceFromSlave(CAP);
      trainPosition = BASE;
      break;
    default:
      Serial.println("Unknown current position");
      break;
  }
}
