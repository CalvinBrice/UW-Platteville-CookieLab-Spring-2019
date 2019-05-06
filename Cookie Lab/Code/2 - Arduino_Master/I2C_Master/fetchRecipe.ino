void fetchRecipe() {
  while (!Serial.available());
  int leng = Serial.read(); // Length of recipe (i.e. number of ingredients)
  while (Serial.available() < leng); // Waits for entire recipe before proceeding
  int buf[leng];
  for (int i = 0; i < leng; i++) buf[i] = Serial.read();
  for (int i = 0; i < leng; i++) ingredient[i].quantity = buf[i];
  //  for (int i = 0; i < leng; i++) Serial.println(ingredient[i].quantity);
}
