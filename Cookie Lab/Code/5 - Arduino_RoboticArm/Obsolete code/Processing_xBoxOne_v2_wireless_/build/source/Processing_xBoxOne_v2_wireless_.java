import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 
import net.java.games.input.*; 
import org.gamecontrolplus.*; 
import org.gamecontrolplus.gui.*; 
import cc.arduino.*; 
import org.firmata.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class Processing_xBoxOne_v2_wireless_ extends PApplet {








ControlDevice cont;
ControlIO control;
Arduino arduino;

//float thumb;
float grip;    // Stores servo angle of gripper right finger
float wristRotationCW;     // Stores servo angle of gripper left finger
float wristRotationCCW;          // Stores servo angle of gripper wrist
float baseRotation;   // Stores servo angle of gripper rotation
float verticalTravel; // Stores Nema 23 vertical height position

public void setup() {
   // Sets screen size
  // Initialise the ControlIO
  control = ControlIO.getInstance(this);
  // Find a device that matches the configuration file
  cont = control.getMatchedDevice("xbsone"); // loads data file in sketch folder to map values from controller

  if (cont == null) {
    println("no controller detected"); // error message
    System.exit(-1);
  }
  println(Arduino.list());
  arduino = new Arduino(this, Arduino.list()[2], 57600); // enumerates connected USB ports
  arduino.pinMode(10, Arduino.SERVO); // initiates servo on pin
  arduino.pinMode(9, Arduino.SERVO); // initiates servo on pin
}

public void getUserInput() {
  grip = map(cont.getSlider("servoPos").getValue(), -1, 1, 0, 180);
  //boolean dilated = cont.getButton("PUPILSIZE1").pressed()
}

public void draw() {
  getUserInput();
  background(grip, 100, 255);
  arduino.servoWrite(10, (int)grip);
}
  public void settings() {  size(360, 200); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "Processing_xBoxOne_v2_wireless_" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
