/*------------------------------------------------------------------------------------
 SerialPortSelection
 
 Adds interface to select from connected serial ports
 ------------------------------------------------------------------------------------*/

Serial serial_port = null;        // the serial port

// serial port buttons
Button btn_serial_up;              // move up through the serial port list
Button btn_serial_dn;              // move down through the serial port list
Button btn_serial_connect;         // connect to the selected serial port
Button btn_serial_disconnect;      // disconnect from the serial port
Button btn_serial_list_refresh;    // refresh the serial port list

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

void serialButtonDraw() { // draw the buttons in the application window
  // draw the text box containing the selected serial port
  DrawTextBox("Select Port", serial_list, 10, 10, 120, 60);
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