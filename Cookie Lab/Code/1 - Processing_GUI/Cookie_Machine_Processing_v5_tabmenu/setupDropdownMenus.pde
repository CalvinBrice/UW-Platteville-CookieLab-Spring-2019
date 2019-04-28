// Create dropdown menus
void setupDropdownMenus() {
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


//cp5.getController("sliderValue").moveTo("Settings");