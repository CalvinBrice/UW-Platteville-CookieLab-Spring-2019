// Create sliders
void setupSliders() {
  for (int i = 0; i<Ingredient.length; i++) {
    cp5.addSlider(Ingredient[i]) // Bay 1
      //.setValue(5)
      .setPosition(xBorder + i*xSpace, 55+tempDist) // .setPosition(xBorder + i*xSpace, 150)
      .setSize(50, 300)
      .setRange(0, 10)
      .setNumberOfTickMarks(11);
  }
}

//cp5.getController("sliderValue").moveTo("Settings");