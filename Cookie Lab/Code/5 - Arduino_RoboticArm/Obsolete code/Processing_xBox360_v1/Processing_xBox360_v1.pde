import processing.serial.*;
import net.java.games.input.*;
import org.gamecontrolplus.*;
import org.gamecontrolplus.gui.*;
import cc.arduino.*;
import org.firmata.*;

ControlDevice cont;
ControlIO control;
Arduino arduino;

//float thumb;
float rightFinger;    // Stores servo angle of gripper right finger
float leftFinger;     // Stores servo angle of gripper left finger
float wrist;          // Stores servo angle of gripper wrist
float baseRotation;   // Stores servo angle of gripper rotation
float verticalTravel; // Stores Nema 23 vertical height position

void setup() {
  size(360, 200); // Sets screen size
  control = ControlIO.getInstance(this);
  cont = control.getMatchedDevice("xbs"); // loads data file in sketch folder to map values from controller

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
  thumb = map(cont.getSlider("servoPos").getValue(), -1, 1, 0, 180);
}

void draw() {
  getUserInput();
  background(thumb, 100, 255);
  arduino.servoWrite(10, (int)thumb);
}
