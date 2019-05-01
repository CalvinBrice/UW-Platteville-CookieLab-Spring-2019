int[] list = new int[numbOfIngredients];

void sendToArduinoMaster() {
  sorting();
  serial_port.write(numbOfIngredients);
  for (int i = 0; i< numbOfIngredients; i++) {
    list[i] = int(round(ingredient[i].getAmount()));
    //list[i] = int(round(bayNumber[i].getValue()));
    //println(list[i]);
    serial_port.write(list[i]);
  }
}

void types(String a) {
  println("it's a String");
}
void types(int a)   {
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
