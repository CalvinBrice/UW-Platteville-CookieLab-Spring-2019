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
  cp5.setFont(createFont("Verdana", 14));

  serialSelectionSetup();

  //Sliders
  createSliders();

  //Buttons
  createButtons();
  javax.swing.JOptionPane.showMessageDialog(null, "Please set Serial Port");
}

void draw() {
  background(myColorBackground);
  serialButtonDraw();
}