// Ingredient bay order (starts from zero)
Ingredients[] ingredient;

//Add struct class
class Ingredients {
  String name;
  int quantity;

  //Constructor
  Ingredients(String tempName, int tempQuantity) {
    name = tempName;
    quantity = tempQuantity;
  }
  String IngName() {
    return name;
  }
  int IngQuantity() {
    return quantity;
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
