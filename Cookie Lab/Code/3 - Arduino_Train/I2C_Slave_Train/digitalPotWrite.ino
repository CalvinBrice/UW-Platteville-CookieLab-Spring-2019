void digitalPotWrite(int value) {
  digitalWrite(CS, LOW);  // Says hello to digital pot
  SPI.transfer(ADDRESS);  // Tells digital pot what's going to happen (adjust resistance)
  SPI.transfer(value);  // Set digital pot to <value> resistance
  digitalWrite(CS, HIGH); // Says goodbye to digital pot
}
