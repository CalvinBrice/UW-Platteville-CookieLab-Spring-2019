void requestInfoFromSlave(int slave, int sensor) {
  bool atOrigin = false; // A dummy variable to note the location of the train relative to the origin
  bool readyForIng = false; // A dummy variable to keep track of train movement

  if (sensor == CAP_SENSOR) {
    Wire.beginTransmission(TRAIN);
    Wire.write(sensor);
    Wire.endTransmission(TRAIN);
    while (!atOrigin) {
      Wire.requestFrom(TRAIN, 1); // Requesting a single byte from the train slave
      while (!Wire.available());
      atOrigin = Wire.read(); // Byte is from the capacitance sensor
    }
  }
  else if (sensor == ULTRASONIC1 || sensor == ULTRASONIC2) {
    Wire.beginTransmission(TRAIN);
    Wire.write(sensor);
    Wire.endTransmission(TRAIN);
    while (!readyForIng) {
      Wire.requestFrom(TRAIN, 1); // Requesting a single byte from the train slave
      while (!Wire.available());
      readyForIng = Wire.read(); // Train and dispenser are ready to proceed to the next applicable ingredient
    }
  }
}

void requestInfoFromSlave(int slave) { // Function overloading
  bool doneDispensing = false; // A dummy variable to keep track of dispensing
  Wire.beginTransmission(DISPENSER);
  Wire.write(sensor); // Analog sensor 1, Analog sensor 2, cap sensor <<<<<<<<<<<<<<<<<<<<<<<<<<
  Wire.endTransmission(DISPENSER);
  while (!doneDispensing) {
    Wire.requestFrom(DISPENSE, 1); // Requesting a single byte from the train slave
    while (!Wire.available());
    doneDispensing = Wire.read(); // Train and dispenser are ready to proceed to the next applicable ingredient
  }
}
