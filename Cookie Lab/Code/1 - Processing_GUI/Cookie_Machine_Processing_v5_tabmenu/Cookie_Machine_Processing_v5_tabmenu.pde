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
import java.util.*;

ControlP5 cp5;


int myColorBackground = color(20, 20, 20);
String val;     // Data received from the serial port

// explore controlp5 tab feature for menus?

int xBorder = 50;   //Space for the first slider
int xSpace = 120;   //Spacing between sliders
int tempDist = 130; //Moving the sliders and button down a little for the dropdown lists until we figure out how to make a new, password accessible window


void setup() {
  size(1400, 600); // use fullscreen() eventually
  background(myColorBackground);
  cp5 = new ControlP5(this);
  cp5.setFont(createFont("Verdana", 14));

  setIngredients();

  // Setup elements
  setupTabs();
  setupSerialSelection();
  setupSliders();
  setupButtons();
  setupDropdownMenus();
}

void draw() {
  background(myColorBackground);
  updateComPorts();
  updateIngredients();
}