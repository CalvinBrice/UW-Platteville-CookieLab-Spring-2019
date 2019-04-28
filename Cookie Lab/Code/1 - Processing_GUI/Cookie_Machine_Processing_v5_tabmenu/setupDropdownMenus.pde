// Create dropdown menus
void setupDropdownMenus() {
  DropdownList[] bayNumber = new DropdownList[numbOfIngredients];
  for (int j = 0; j<numbOfIngredients; j++) {
    String bayLabel = "bay" + str(j);
    bayNumber[j] = cp5.addDropdownList(bayLabel)
      .setPosition(xBorder + j*xSpace-5, 20+tempDist)
      .setSize(110, 300);
    customize(bayNumber[j], j); // customize the second list
  }
}

// Customize the dropdown menus
void customize(DropdownList ddl, int index) {
  ddl.setBackgroundColor(color(196));
  ddl.setItemHeight(20);
  ddl.setBarHeight(25);
  ddl.getCaptionLabel().set("Bay "+str(index));
  ddl.setItems(IngredientList);
  ddl.setColorBackground(color(60));
  ddl.setColorActive(color(255, 128));
  ddl.setOpen(false);
}


//cp5.getController("sliderValue").moveTo("Settings");
