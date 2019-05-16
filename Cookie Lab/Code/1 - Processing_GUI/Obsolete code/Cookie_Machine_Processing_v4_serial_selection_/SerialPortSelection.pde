/*------------------------------------------------------------------------------------
 SerialPortSelection
 
 Adds interface to select from connected serial ports
 ------------------------------------------------------------------------------------*/

Serial serial_port = null;        // the serial port

String serial_list;                // list of serial ports
int serial_list_index = 0;         // currently selected serial port 
int num_serial_ports = 0;          // number of serial ports in the list

void serialSelectionSetup() {
  // create the buttons for the serial selector
  cp5.addButton("serial_up")
    .setLabel("^")
    .setPosition(140, 10) // x, y
    .setSize(40, 25); // width, height

  cp5.addButton("serial_dn")
    .setLabel("v")
    .setPosition(140, 45) // x, y
    .setSize(40, 25); // width, height

  cp5.addButton("serial_connect")
    .setLabel("Connect")
    .setPosition(190, 10) // x, y
    .setSize(100, 25); // width, height

  cp5.addButton("serial_disconnect")
    .setLabel("Disconnect")
    .setPosition(190, 45) // x, y
    .setSize(100, 25); // width, height

  cp5.addButton("serial_list_refresh")
    .setLabel("Refresh")
    .setPosition(190, 80) // x, y
    .setSize(100, 25); // width, height

  // get the list of serial ports on the computer
  serial_list = Serial.list()[serial_list_index];

  // get the number of serial ports in the list
  num_serial_ports = Serial.list().length;
}

// function for drawing a text box with title and contents
void DrawTextBox(String title, String str, int x, int y, int w, int h)
{
  fill(255);
  rect(x, y, w, h);
  fill(0);
  textAlign(LEFT);
  textSize(14);
  text(title, x + 10, y + 10, w - 20, 20);
  textSize(12);  
  text(str, x + 10, y + 40, w - 20, h - 10);
}