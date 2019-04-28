// Create sliders
void setupSliders() {
  for (int i = 0; i<numbOfIngredients; i++) {
    cp5.addSlider(ingredient[i].Identity()) // Bay 1
      .setPosition(xBorder + i*xSpace, 55+tempDist) // .setPosition(xBorder + i*xSpace, 150)
      .setSize(50, 300)
      .setRange(0, 10)
      .setNumberOfTickMarks(11)
      .setValue(ingredient[i].Amount())
      .setDecimalPrecision(0);
    cp5.getController(ingredient[i].Identity()).getCaptionLabel();
    cp5.getController(ingredient[i].Identity()).getValueLabel().align(ControlP5.CENTER, ControlP5.TOP_OUTSIDE).setPaddingY(0);
  }
}

//cp5.getController("sliderValue").moveTo("Settings");
