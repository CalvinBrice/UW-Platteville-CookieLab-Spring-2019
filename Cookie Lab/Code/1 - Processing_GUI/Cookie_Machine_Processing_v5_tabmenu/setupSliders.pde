// Create sliders
void setupSliders() {
  for (int i = 0; i<numbOfIngredients; i++) {
    cp5.addSlider(ingredient[i].Identity()) // Bay 1
      .setPosition(xBorder + i*xSpace, 0+tempDist) // .setPosition(xBorder + i*xSpace, 150)
      .setSize(50, 300)
      .setRange(0, 10)
      .setNumberOfTickMarks(11)
      .setValue(ingredient[i].Amount()) // Starts each slider at zero
      .setDecimalPrecision(0)
      .setLabelVisible(false);
      ;
  }
}

//cp5.getController("sliderValue").moveTo("Settings");
