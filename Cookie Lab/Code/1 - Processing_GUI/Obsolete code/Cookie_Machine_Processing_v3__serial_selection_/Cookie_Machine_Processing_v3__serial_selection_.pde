/*------------------------------------------------------------------------------------
 Program:     Cookie Lab GUI
 Description:       
 Purpose:                   
 Hardware:       
 
 Date:        24 April 2019   Author:   Calvin Brice, Nicholas Gorichs
 ------------------------------------------------------------------------------------*/

import controlP5.*;
import processing.serial.*;

ControlP5 controlP5;
ControlP5 cp5;

int myColorBackground = color(0, 0, 0);
String val;     // Data received from the serial port

int xBorder = 50; //Space for the first slider
int xSpace = 120; //Spacing between sliders  
int tempDist = 100; //Moving the sliders and button down a little for the dropdown lists until we figure out how to make a new, password accessible window.

void setup() {
  size(1400, 625);
  background(myColorBackground);
  cp5 = new ControlP5(this);

  serialSelectionSetup();

  cp5.setFont(createFont("Verdana", 14));
  DropdownList[] bayNumber = new DropdownList[Ingredient.length];
  //Sliders and Dropdown Menus
  for (int i = 0; i<Ingredient.length; i++) {
    // create a second DropdownList
    String baystr = "bay";
    String baystrj = str(i);
    String bayLabel = baystr + baystrj;
    bayNumber[i] = cp5.addDropdownList(bayLabel)
      .setPosition(xBorder + i*xSpace-30, 40+tempDist)
      .setSize(110, 50)
      ;
    customize(bayNumber[i]); // customize the second list

    //String textstr = "sliderValue";
    //String textstri = str(i);
    //String textLabel = textstr+textstri;
    cp5.addSlider(Ingredient[i]) // Bay 1
      //.setValue(5)
      .setPosition(xBorder + i*xSpace-5, 80+tempDist)
      .setSize(50, 300)
      .setRange(0, 10)
      .setLabelVisible(true)
      .setNumberOfTickMarks(11);
    //myTextArea = cp5.addTextarea(textLabel)
    //  .setPosition(xBorder + i*xSpace+5, 80+tempDist)
    //  .setSize(40, 25)
    //  .setFont(createFont("arial", 12))
    //  .setLineHeight(14)
    //  .setColor(color(255))
    //  .setColorBackground(color(0,0))//0,0
    //  .setColorForeground(color(0,0));//255,255
    //;
    //String sliderValue = str(cp5.getValue(textLabel));
    //myTextArea.setText(sliderValue);
  } 

  //Buttons
  cp5.addButton("Dispense")
    .setPosition((width/2)-75, 550) //xBorder + 0*xSpace
    .setSize(150, 50);
}

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

void draw() {
  background(myColorBackground);
  //text("Cookie Machine Controller", 40, 30);  // ("text", x coordinate, y coordinate)
  // draw the buttons in the application window
  serialButtonDraw();
}

void controlEvent(ControlEvent theEvent) {

  if (theEvent.isController()) {  
    if (theEvent.getController().getName()=="Dispense") {
      println("Dispense");
      print("Writing value to ");
      print(serial_list);
      print(": ");
      println(Sugar);
      //int y = Sugar;
      serial_port.write(Sugar);
      //for (int i = 0; i<Ingredient.length; i++) {
      //  serial_port.write(Ingredient[i]);
      //  //serial_port.write("Dispense Ingredients");
      //}
    }

    //// dragging slider1 changes the value of slider2
    //if (theEvent.getController().getName()=="Sugar") {
    //  float sugar = theEvent.getController().getValue();
    //  // prevent warnings at start
    //  if (controlP5.getController("Sugar") != null) {
    //    //controlP5.getController("slider2").setValue(value);
    //  }
    //}


    //// changing the value of numberbox1 turns knob1
    //if(theEvent.getController().getName()=="numberbox1") {
    //controlP5.getController("knob1").setValue(theEvent.getController().getValue());
    //}
  }
}
