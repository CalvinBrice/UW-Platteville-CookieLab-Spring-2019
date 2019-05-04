int[] list = new int[numbOfIngredients];

void sendToArduinoMaster() {
  //sorting();
  println(numbOfIngredients);
  serial_port.write(numbOfIngredients);
  for (int i = 0; i < numbOfIngredients; i++) {
    for (int j = 0; j < numbOfIngredients; j++) {
      if (ingredient[j].getLocation() == i) {
        list[i] = int(round(ingredient[j].getAmount()));
        println(list[i]);
        serial_port.write(list[i]);
      }
      continue;
    }
  }
}

void types(String a) {
  println("it's a String");
}
void types(int a) {
  println("it's an int");
}
void types(char a) {
  println("it's a char*");
}
void types(float a) {
  println("it's a float");
}
void types(byte a) {
  println("it's a byte");
}