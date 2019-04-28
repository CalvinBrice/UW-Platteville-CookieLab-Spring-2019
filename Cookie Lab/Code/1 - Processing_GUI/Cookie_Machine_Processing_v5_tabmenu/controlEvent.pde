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
        println(ingredient[0].IngQuantity());
        //serial_port.write(Sugar);
      } else {
        javax.swing.JOptionPane.showMessageDialog(null, "Please set Serial Port"); //Pop up error message
      }
    }

    // Connect button clicked
    if (theEvent.getController().getName()=="serial_connect") {
      if (serial_port == null) {
        // connect to the selected serial port
        serial_port = new Serial(this, Serial.list()[serial_list_index], 9600);
        print(serial_list);
        println(": Connected");
      } else {
        print("Please disconnect from ");
        print(serial_list);
        println(" before connecting to another port");
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
        //javax.swing.JOptionPane.showMessageDialog(null, "Please set Serial Port");
      }
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
