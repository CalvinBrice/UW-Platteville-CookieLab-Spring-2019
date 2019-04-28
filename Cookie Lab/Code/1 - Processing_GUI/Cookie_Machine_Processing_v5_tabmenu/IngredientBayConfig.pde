// Ingredient bay order (starts from zero)
Ingredients[] ingredient;

//Add struct class
class Ingredients {
  String name;
  float quantity;

  //Constructor
  Ingredients(String tempName, int tempQuantity) {
    name = tempName;
    quantity = tempQuantity;
  }
  String Identity() {
    return name;
  }
  float Amount() {
    return quantity;
  }
  void Update() {
    for (int r = 0; r<numbOfIngredients; r++) {
      quantity = cp5.getController(ingredient[r].Identity()).getValue();
    }
  }
};

String IngredientList[] = {  
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

int numbOfIngredients = IngredientList.length;

void setIngredients() {
  ingredient = new Ingredients[numbOfIngredients];
  for (int k = 0; k<numbOfIngredients; k++) {
    ingredient[k] = new Ingredients(IngredientList[k], 0);
  }
}

void updateIngredients() {
  for (int i=0; i<numbOfIngredients; i++) {
    ingredient[i].Update();
  }
}
