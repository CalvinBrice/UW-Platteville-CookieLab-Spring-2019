/*------------------------------------------------------------------------------------
 Program:     Cookie Lab GUI
 Description:       
 Purpose:                   
 Hardware:       
 
 Date:        24 April 2019   Author:   Calvin Brice, Nicholas Gorich
 ------------------------------------------------------------------------------------*/

import controlP5.*;
import processing.serial.*;

ControlP5 controlP5;
ControlP5 cp5;

int myColorBackground = color(0, 0, 0);
String val;     // Data received from the serial port

int xBorder = 50; //Space for the first slider
int xSpace = 120; //Spacing between sliders


void setup() {
  size(1350, 600);
  background(myColorBackground);
  cp5 = new ControlP5(this);

  serialSelectionSetup();

  cp5.setFont(createFont("Verdana", 14));

  //Sliders
  for (int i = 0; i<11; i++) {
    cp5.addSlider(Ingredient[i]) // Bay 1
      .setValue(5)
      .setPosition(xBorder + i*xSpace, 150)
      .setSize(50, 300)
      .setRange(0, 10)
      .setNumberOfTickMarks(11);
  } 

  //Buttons
  cp5.addButton("Dispense")
    .setPosition((width/2)-75, 500) //xBorder + 0*xSpace
    .setSize(150, 50);
}

void draw() {
  background(myColorBackground);
  //text("Cookie Machine Controller", 40, 30);  // ("text", x coordinate, y coordinat)
  // draw the buttons in the application window
  serialButtonDraw();
}


void controlEvent(ControlEvent theEvent) {

  if (theEvent.isController()) {  
    if (theEvent.getController().getName()=="Dispense") {
      println("Dispense");
      //myPort.write("!Salt 1\r");
    }

    //// dragging slider1 changes the value of slider2
    //if (theEvent.getController().getName()=="slider1") {
    //  float value = theEvent.getController().getValue();
    //  // prevent warnings at start
    //  if (controlP5.getController("slider2") != null) {
    //    //controlP5.getController("slider2").setValue(value);
    //  }
    //}


    //// changing the value of numberbox1 turns knob1
    //if(theEvent.getController().getName()=="numberbox1") {
    //controlP5.getController("knob1").setValue(theEvent.getController().getValue());
    //}
  }
}