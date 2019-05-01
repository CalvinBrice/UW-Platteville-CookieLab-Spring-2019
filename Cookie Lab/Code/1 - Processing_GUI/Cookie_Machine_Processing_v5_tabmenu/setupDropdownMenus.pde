// Create dropdown menus
DropdownList[] bayNumber = new DropdownList[numbOfIngredients];

void setupDropdownMenus() {
  Group g1 = cp5.addGroup("g1")
    .moveTo("Settings") //moves to settings tab;
    .setVisible(false);
  for (int j = 0; j<numbOfIngredients; j++) {
    String bayLabel = "bay" + str(j);
    bayNumber[j] = cp5.addDropdownList(bayLabel)
      .setGroup(g1)
      .setPosition(xBorder + j*xSpace-5, 5+tempDist)
      .setSize(110, 500)
      .setValue(BayList[j]);
    customize(bayNumber[j], j); // customize the second list
  }

  setupPassword();
}

// Customize the dropdown menus
void customize(DropdownList ddl, int index) {
  ddl.setBackgroundColor(color(196));
  ddl.setItemHeight(40);
  ddl.setBarHeight(25);
  ddl.getCaptionLabel().set("Bay "+str(index+1));
  ddl.setItems(IngredientList);
  ddl.setColorBackground(color(60));
  ddl.setColorActive(color(255, 128));
  ddl.setOpen(false);
}


void setupPassword() {
  cp5.addTextfield("checkPassword")
    .setLabel("Password")
    .moveTo("Settings") //moves to settings tab
    .setPosition(500, 50)
    .setSize(200, 40)
    .setFont(font)
    .setFocus(true)
    .setColor(color(0, 255, 0))
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.BOTTOM_OUTSIDE)
    ;

  cp5.addBang("enterPassword")
    .setLabel("Enter")
    .moveTo("Settings") //moves to settings tab
    .setPosition(500+210, 50)
    .setSize(100, 40)
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
    ;

  cp5.addBang("logout")
    .setLabel("Logout")
    .moveTo("Settings") //moves to settings tab
    .setGroup("g1")
    .setPosition(820, 50)
    .setSize(100, 40)
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
    ;
}

String settingsPassword = "password"; // Do I really need to explain this... I'm not even obfusticating it much

public void enterPassword() {
  String temp = cp5.get(Textfield.class, "checkPassword").getText();
  if (settingsPassword.equals(temp)) {
    println("password is correct");
    cp5.getGroup("g1")
      .setVisible(true);
  } else {
    println("password is incorrect");
  }
  cp5.get(Textfield.class, "checkPassword").clear();
}

public void logout() {
  cp5.getGroup("g1")
    .setVisible(false);
  println("logged out");
}

public void checkPassword(String theText) {
  // automatically receives results from controller input
  //println("a textfield event for controller 'input' : "+theText);
  //println(settingsPassword);
  if (settingsPassword.equals(theText)) {
    println("password is correct");
    cp5.getGroup("g1")
      .setVisible(true);
  } else {
    println("password is incorrect");
  }
}
