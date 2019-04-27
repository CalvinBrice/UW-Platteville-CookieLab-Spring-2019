/*------------------------------------------------------------------------------------
 Program:     Cookie Lab GUI
 Description:       
 Purpose:                   
 Hardware:       
 
 Date:        27 April 2019   
 Author(s):   Calvin Brice, Nicholas Gorichs
 ------------------------------------------------------------------------------------*/

import controlP5.*;
import processing.serial.*;

ControlP5 controlP5;
ControlP5 cp5;

int myColorBackground = color(0, 0, 0);
String val;     // Data received from the serial port

int xBorder = 50; //Space for the first slider
int xSpace = 120; //Spacing between sliders
int tempDist = 100; //Moving the sliders and button down a little for the dropdown lists until we figure out how to make a new, password accessible window


void setup() {
  size(1400, 600);
  background(myColorBackground);
  cp5 = new ControlP5(this);
  cp5.setFont(createFont("Verdana", 14));

  serialSelectionSetup();

  //Dropdown Menus
  createDropdownMenus();

  //Sliders
  createSliders();

  //Buttons
  createButtons();
  javax.swing.JOptionPane.showMessageDialog(null, "Please set Serial Port");
}

void draw() {
  background(myColorBackground);
  DrawTextBox("Select Port", serial_list, 10, 10, 120, 60);
}
