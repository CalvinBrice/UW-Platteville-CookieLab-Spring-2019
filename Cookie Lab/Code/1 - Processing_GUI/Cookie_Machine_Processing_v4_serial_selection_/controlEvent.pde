//Handles slider/button events

void controlEvent(ControlEvent theEvent) {
  if (theEvent.isController()) {  

    // Dispense button clicked (currently testing i2c connection)
    if (theEvent.getController().getName()=="Dispense") {
      if (serial_port != null) {
        println("Dispense");
        print("Writing value to ");
        print(serial_list);
        print(": ");
        println(Sugar);
        //serial_port.write(Sugar);
      } else {
        javax.swing.JOptionPane.showMessageDialog(null, "Please set Serial Port"); //Pop up error message
      }
    }

    // Serial up button clicked
    if (theEvent.getController().getName()=="serial_up") {
      if (serial_list_index > 0) {
        // move one position up in the list of serial ports
        serial_list_index--;
        serial_list = Serial.list()[serial_list_index];
      }
    }

    // Serial down button clicked
    if (theEvent.getController().getName()=="serial_dn") {
      if (serial_list_index < (num_serial_ports - 1)) {
        // move one position down in the list of serial ports
        serial_list_index++;
        serial_list = Serial.list()[serial_list_index];
      }
    }

    // Connect button clicked
    if (theEvent.getController().getName()=="serial_connect") {
      if (serial_port == null) {
        // connect to the selected serial port
        serial_port = new Serial(this, Serial.list()[serial_list_index], 9600);
        print(serial_list);
        println(": Connected");
      }
    }

    // Disconnect button clicked
    if (theEvent.getController().getName()=="serial_disconnect") {
      if (serial_port != null) {
        // disconnect from the serial port
        serial_port.stop();     
        print(serial_list);
        println(": Disconnected");
        serial_port = null;
        javax.swing.JOptionPane.showMessageDialog(null, "Please set Serial Port");
      }
    }

    // Refresh button clicked
    if (theEvent.getController().getName()=="serial_list_refresh") {
      // get the serial port list and length of the list
      serial_list = Serial.list()[serial_list_index];
      num_serial_ports = Serial.list().length;
      println("COM list refreshed");
    }

    //// dragging slider1 changes the value of slider2
    //if (theEvent.getController().getName()=="Sugar") {
    //  float sugar = theEvent.getController().getValue();
    //  // prevent warnings at start
    //  if (controlP5.getController("Sugar") != null) {
    //    //controlP5.getController("slider2").setValue(value);
    //  }
    //}


    //// changing the value of numberbox1 turns knob1
    //if(theEvent.getController().getName()=="numberbox1") {
    //controlP5.getController("knob1").setValue(theEvent.getController().getValue());
    //}
  }
}