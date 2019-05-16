/*------------------------------------------------------------------------------------
 SerialPortSelection
 
 Adds interface to select from connected serial ports
 ------------------------------------------------------------------------------------*/

Serial serial_port = null;        // the serial port

String serial_list;                // list of serial ports
int serial_list_index = 0;         // currently selected serial port 
int num_serial_ports = 0;          // number of serial ports in the list

void setupSerialSelection() {

  cp5.addButton("serial_connect")
    .moveTo("Settings") //moves to settings tab
    .setLabel("Connect")
    .setPosition(140, 40) // x, y
    .setSize(110, 25); // width, height

  cp5.addButton("serial_disconnect")
    .moveTo("Settings") //moves to settings tab
    .setLabel("Disconnect")
    .setPosition(140, 75) // x, y
    .setSize(110, 25); // width, height


  // get the list of serial ports on the computer
  serial_list = Serial.list()[serial_list_index];
  List serial_list_view = Arrays.asList(Serial.list());

  // get the number of serial ports in the list
  num_serial_ports = Serial.list().length;

  /* add a ScrollableList, by default it behaves like a DropdownList */
  cp5.addScrollableList("COMPorts")
    .moveTo("Settings") //moves to settings tab
    .setLabel("Select Port")
    .setPosition(10, 40)
    .setSize(120, 400)
    .setBarHeight(30)
    .setItemHeight(30)
    .addItems(serial_list_view)
    .setType(ScrollableList.DROPDOWN) // currently supported DROPDOWN and LIST
    ;
}

void COMPorts(int n) {
  serial_list_index = n;
  serial_list = Serial.list()[serial_list_index];
  //println(serial_list);
}

void updateComPorts() { // provides a constantly refreshed list
  serial_list = Serial.list()[serial_list_index];
  num_serial_ports = Serial.list().length;
  List serial_list_view = Arrays.asList(Serial.list());
  cp5.get(ScrollableList.class, "COMPorts").setItems(serial_list_view);
}