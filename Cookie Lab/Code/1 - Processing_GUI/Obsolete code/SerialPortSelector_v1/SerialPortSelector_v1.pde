import processing.serial.*;
import controlP5.*;
 
ControlP5 cp5;
DropdownList d1;
 
Serial myPort;
 
String portName;
int serialListIndex;
 
void setup() {
  clear();
  size(700, 400 );
  cp5 = new ControlP5(this);
 
  PFont pfont = createFont("Arial",10,true); //Create a font
  ControlFont font = new ControlFont(pfont,20); //font, font-size
 
  d1 = cp5.addDropdownList("myList-d1")
          .setPosition(100, 100)
          .setSize(100, 200)
          .setHeight(210)
          .setItemHeight(40)
          .setBarHeight(50)
          .setFont(font)
          .setColorBackground(color(60))
          .setColorActive(color(255, 128))
          ;
 
      d1.getCaptionLabel().set("PORT"); //set PORT before anything is selected
 
      portName = Serial.list()[0]; //0 as default
      myPort = new Serial(this, portName, 9600);
}
 
void draw() {
  background(128);
 
  if(d1.isMouseOver()) {
   d1.clear(); //Delete all the items
   for (int i=0;i<Serial.list().length;i++) {
     d1.addItem(Serial.list()[i], i); //add the items in the list
   }
  }
  if ( myPort.available() > 0) {  //read incoming data from serial port
    println(myPort.readStringUntil('\n')); //read until new input
   } 
}
 
void controlEvent(ControlEvent theEvent) { //when something in the list is selected
    myPort.clear(); //delete the port
    myPort.stop(); //stop the port
    if (theEvent.isController() && d1.isMouseOver()) {
    portName = Serial.list()[int(theEvent.getController().getValue())]; //port name is set to the selected port in the dropDownMeny
    myPort = new Serial(this, portName, 9600); //Create a new connection
    println("Serial index set to: " + theEvent.getController().getValue());
    delay(2000); 
    }
}