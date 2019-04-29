Textlabel[] ingredientNameLabel= new Textlabel[numbOfIngredients];
Textlabel[] ingredientValueLabel= new Textlabel[numbOfIngredients];

void setupTextLabels() {
  for (int i =0; i<numbOfIngredients; i++) {
    String identity = ingredient[i].Identity();
    int temp = round(ingredient[i].Amount());
    identity = identity.toUpperCase();
    ingredientNameLabel[i] = cp5.addTextlabel("Name"+str(i))
      .setText(identity)
      .setTab("default") //moves to settings tab
      .setFont(font)
      .setColor(color(255, 255, 255))
      .setPosition(xBorder+i*xSpace, 430)
      .setSize(100, 40)
      .setMultiline(true)
      //.align(ControlP5.CENTER,ControlP5.CENTER,ControlP5.CENTER,ControlP5.CENTER) // Doesn't seem to do anything. Can't figure out how to center align the text
      ;
    ingredientValueLabel[i] = cp5.addTextlabel("Amount"+str(i))
      .setText(str(temp))
      .setTab("default") //moves to settings tab
      .setFont(font)
      .setColor(color(255, 255, 255))
      .setPosition(xBorder+i*xSpace+17, 110)
      ;
  }
}
