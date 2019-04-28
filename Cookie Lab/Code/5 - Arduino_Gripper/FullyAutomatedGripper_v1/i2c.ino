// Format of messages to be received is:
// (int FINGER, int WRIST, int HEIGHT, int, ROTATION)

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  //Order of instructions sent and received is critical, maximum of 32 bytes can be transmitted/received
  finger_pos = Wire.read();
  wrist_pos = Wire.read();
  height_pos = Wire.read();
  rotation_pos = Wire.read();
  if (debug == true){
    Debug();
  }
}

void Debug(){
  Serial.print("finger_pos: ");
  Serial.println(finger_pos);
  Serial.print("wrist_pos: ");
  Serial.println(wrist_pos);
  Serial.print("height_pos: ");
  Serial.println(height_pos);
  Serial.print("rotation_pos: ");
  Serial.println(rotation_pos);
}
