float[] list = new float[numbOfIngredients];

void sendToArduinoMaster() {
  for (int i = 0; i< numbOfIngredients; i++) {
    for (int j = 0; j< numbOfIngredients; j++) {
      list[i] = bayNumber[i].getValue();
    }
  }
}
