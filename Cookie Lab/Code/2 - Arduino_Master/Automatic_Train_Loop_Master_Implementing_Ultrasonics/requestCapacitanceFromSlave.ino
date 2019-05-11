void requestCapacitanceFromSlave(int sensor) {
  Wire.beginTransmission(TRAIN);
  Wire.write(CAP_CONTROL);
  Wire.endTransmission(TRAIN);
  Wire.requestFrom(TRAIN, 1);
  while (!Wire.available()); // Should be stuck here until the capacitance sensor is triggered
  capSensorTriggered = Wire.read();
}

