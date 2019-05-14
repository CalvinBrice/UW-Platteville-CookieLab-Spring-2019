//----------------------------------------
// i2c handler
//
//----------------------------------------

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  
  //Nick add receiving code here
  while(!Wire.available());
  mainInControl = Wire.read(); // Sets mainInControl to false giving the ARM master control
  
  //Call "runAutomation();"
}

void runAutomation() {
  //Calvin will fill in here
  Serial.println("Begin automated procedure");
  
  
  Wire.begin(MASTER); // Gives the main arduino master control (This will go at the end of the runAutomation() function)
  Wire.write(true); // Sets MASTER's 'mainInControl' variable to true
  Wire.endTransmission();
  mainInControl = true;
}
