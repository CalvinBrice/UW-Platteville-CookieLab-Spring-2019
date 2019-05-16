// Ingredient bay order (starts from zero)

//Add struct class

String Ingredient[] = {  
  "Sugar", 
  "Butter", 
  "Molasses", 
  "Vanilla", 
  "Egg", 
  "Baking \nSoda", 
  "Chocolate \nChips", 
  "Oats", 
  "Flour", 
  "Salt", 
  "M & M's"
};

int Sugar = 0;
int Butter = 0;
int Molasses = 0;

// Create sliders
void createSliders() {
  for (int i = 0; i<Ingredient.length; i++) {
    cp5.addSlider(Ingredient[i]) // Bay 1
      //.setValue(5)
      .setPosition(xBorder + i*xSpace, 55+tempDist) // .setPosition(xBorder + i*xSpace, 150)
      .setSize(50, 300)
      .setRange(0, 10)
      .setNumberOfTickMarks(11);
  }
}

// Create buttons
void createButtons() {
  cp5.addButton("Dispense")
    .setPosition((width/2)-75, 500) //xBorder + 0*xSpace
    .setSize(150, 50);
}

// Create dropdown menus
void createDropdownMenus() {
  DropdownList[] bayNumber = new DropdownList[Ingredient.length];
  //Sliders and Dropdown Menus
  for (int j = 0; j<Ingredient.length; j++) {
    //String baystr = "bay";
    //String baystrj = str(i);
    String bayLabel = "bay" + str(j);
    bayNumber[j] = cp5.addDropdownList(bayLabel)
      .setPosition(xBorder + j*xSpace-5, 20+tempDist)
      .setSize(110, 50);
    customize(bayNumber[j]); // customize the second list
  }
}

// Customize the dropdown menus
void customize(DropdownList ddl) { // Customizes the dropdown lists
  // a convenience function to customize a DropdownList
  ddl.setBackgroundColor(color(196));
  ddl.setItemHeight(20);
  ddl.setBarHeight(25);
  ddl.getCaptionLabel().set("dropdown");
  for (int i=0; i<40; i++) {
    ddl.addItem("item "+i, i);
  }
  //ddl.scroll(0);
  ddl.setColorBackground(color(60));
  ddl.setColorActive(color(255, 128));
  ddl.setOpen(false);
}
