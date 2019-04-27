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
      .setPosition(xBorder + i*xSpace, 150)
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