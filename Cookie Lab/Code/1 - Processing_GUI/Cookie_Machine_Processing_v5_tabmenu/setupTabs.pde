void setupTabs() {
  // if you want to receive a controlEvent when
  // a  tab is clicked, use activeEvent(true)

  cp5.addTab("Settings")
    .setColorBackground(color(0, 160, 100))
    .setColorLabel(color(255))
    .setColorActive(color(255, 128, 0))
    ;

  // if you want to receive a controlEvent when
  // a  tab is clicked, use activeEvent(true)

  cp5.getTab("default")
    .activateEvent(true)
    .setLabel("Main")
    .setHeight(30)
    .setId(1)
    ;

  cp5.getTab("Settings")
    .activateEvent(true)
    .setLabel("Settings")
    .setHeight(30)
    .setId(2)
    ;
}