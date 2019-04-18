void fetchRecipe() {
  char buffers[16];
  for (int i = 0; i < NUMBER_OF_BAYS; i++) {
    Serial.print("Type amount: ");
    quantity[i] = i+1;
//    while (!Serial.available()) {}
//    Serial.readBytesUntil('\n', buffers, 16);
//    quantity[i] = atoi(buffers);
    Serial.println(quantity[i]);
  }
}
