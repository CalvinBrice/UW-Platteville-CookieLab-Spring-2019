import controlP5.*;
import processing.serial.*;
Serial myPort;

// since we're doing serial handshaking, 
// we need to check if we've heard from the microcontroller
boolean firstContact = false;

ControlP5 controlP5;
ControlP5 cp5;

int myColorBackground = color(0, 0, 0);
String val;     // Data received from the serial port

int xBorder = 50; //Space for the first slider
int xSpace = 120; //Spacing inbetween sliders

// Ingredient Bays
enum { 
  Butter, 
    Sugar, 
    Molasses, 
    Vanilla, 
    Egg, 
    BakingSoda, 
    ChocolateChips, 
    Oats, 
    Flour, 
    Salt, 
    MMs
};

int Butter = Butter;
//int Butter = 1;
//int Sugar = 2;
//int Molasses = 3;
//int Vanilla = 4;
//int Egg = 5;
//int BakingSoda = 6;
//int ChocolateChips = 7;
//int Oats = 8;
//int Flour = 9;
//int Salt = 10;
//int MMs = 11;




void setup() {

  size(1000, 500);
  background(myColorBackground);
  controlP5 = new ControlP5(this);
  cp5 = new ControlP5(this);

  //Needs COM port selector*****************************************
  //printArray(Serial.list());   //prints all available serial ports
  myPort = new Serial(this, "COM3", 9600);
  myPort.bufferUntil('\n'); 

  cp5.setFont(createFont("Verdana", 14));

  //Sliders
  cp5.addSlider("Butter") // Bay 11
    .setValue(5)
    .setPosition(xBorder + 0*xSpace, 50)
    .setSize(50, 300)
    .setRange(0, 10)
    .setNumberOfTickMarks(11)
    ;
  cp5.addSlider("Sugar")
    .setValue(0)
    .setPosition(xBorder + 1*xSpace, 50)
    .setSize(50, 300)
    .setRange(0, 10)
    .setNumberOfTickMarks(11)
    ;
  cp5.addSlider("Molasses")
    .setValue(0)
    .setPosition(xBorder + 2*xSpace, 50)
    .setSize(50, 300)
    .setRange(0, 10)
    .setNumberOfTickMarks(11)
    ;

  //Buttons
  cp5.addButton("Dispense")
    .setPosition(xBorder + 0*xSpace, 400)
    .setSize(150, 50)
    //.setLabel("Dispense Butter")
    ;
}

void draw() {

  background(myColorBackground);
  text("Cookie Machine Controller", 40, 30);  // ("text", x coordinate, y coordinat)
}


void controlEvent(ControlEvent theEvent) {


  if (theEvent.isController()) {  
    if (theEvent.getController().getName()=="Dispense") {
      //println("!Salt 1\r");
      myPort.write("!Salt 1\r");
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

void serialEvent( Serial myPort) {

  //put the incoming data into a String - 
  //the '\n' is our end delimiter indicating the end of a complete packet
  val = myPort.readStringUntil('\n');
  //make sure our data isn't empty before continuing
  if (val != null) {
    //trim whitespace and formatting characters (like carriage return)
    val = trim(val);
    //println(val);

    //look for our 'ping' string to start the handshake
    //if it's there, clear the buffer, and send a request for data
    if (firstContact == false) {
      if (val.equals("ping")) {
        myPort.clear();
        firstContact = true;
        myPort.write("ping");
        println("contact");
      }
    } else { //if we've already established contact, keep getting and parsing data
      println(val);

      //if (mousePressed == true) 
      //{                           //if we clicked in the window
      //  //myPort.write('1');        //send a 1
      //  println("1");
      //}

      // when you've parsed the data you have, ask for more:
      myPort.write("ping");
    }
  }
}
