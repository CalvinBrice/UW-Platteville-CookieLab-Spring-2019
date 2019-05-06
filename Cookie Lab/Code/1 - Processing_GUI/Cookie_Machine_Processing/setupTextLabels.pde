Textlabel[] ingredientNameLabel= new Textlabel[numbOfIngredients];
Textlabel[] ingredientValueLabel= new Textlabel[numbOfIngredients];

void setupTextLabels() {
  for (int j = 0; j<numbOfIngredients; j++) {
    String identity = defaultIngredient[j].getIdentity();
    identity = identity.toUpperCase();
    ingredientNameLabel[j] = cp5.addTextlabel("Name"+str(j))
      .setText(identity)
      .setTab("default") //moves to settings tab
      .setFont(font)
      .setColor(color(255, 255, 255))
      .setPosition(xBorder+j*xSpace, 430)
      .setSize(100, 40)
      .setMultiline(true)
      //.align(ControlP5.CENTER,ControlP5.CENTER,ControlP5.CENTER,ControlP5.CENTER) // Doesn't seem to do anything. Can't figure out how to center align the text
      ;
  }
  for (int k = 0; k<numbOfIngredients; k++) {
    int temp = round(defaultIngredient[k].getAmount());
    ingredientValueLabel[k] = cp5.addTextlabel("Amount"+str(k))
      .setText(str(temp))
      .setTab("default") //moves to settings tab
      .setFont(font)
      .setColor(color(255, 255, 255))
      .setPosition(xBorder+k*xSpace+17, 110)
      ;
  }
}