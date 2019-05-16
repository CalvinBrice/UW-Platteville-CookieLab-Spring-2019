// Adafruit Motor Shield V2 Library - Version: Latest 
#include <Adafruit_MotorShield.h>

// MegunoLink - Version: Latest
#include <MegunoLink.h>
#include <CommandHandler.h>
#include <TCPCommandHandler.h>
#include <ArduinoTimer.h>
#include <CircularBuffer.h>
#include <EEPROMStore.h>
#include <Filter.h>

// Wire - Version: Latest
#include <Wire.h>

#include "CommandHandler.h"
/*
  This code is the backend for running the stepper motors and timing of the dispensing machine
*/

int Steps;
float Step2;
int Jog=20; //defines the step "length" of the jog button
int ButterJog=5000;
int BakingSodaJog=5; 

// 35 is the number of commands that can be assigned in the void setup (this can be changed I think)
CommandHandler<35> SerialCommandHandler;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS_0 = Adafruit_MotorShield(); // default board ID
Adafruit_MotorShield AFMS_1 = Adafruit_MotorShield(0x61); // board ID + 1
Adafruit_MotorShield AFMS_2 = Adafruit_MotorShield(0x62); // board ID + 2
Adafruit_MotorShield AFMS_3 = Adafruit_MotorShield(0x63); // board ID + 3
Adafruit_MotorShield AFMS_4 = Adafruit_MotorShield(0x64); // board ID + 4
Adafruit_MotorShield AFMS_5 = Adafruit_MotorShield(0x65); // board ID + 5

// Connect a stepper motors with 200 steps per revolution (1.8 degree)
Adafruit_StepperMotor *myMotor1 = AFMS_0.getStepper(200, 1); //   Butter
Adafruit_StepperMotor *myMotor2 = AFMS_0.getStepper(200, 2); //   Vanilla
Adafruit_StepperMotor *myMotor3 = AFMS_1.getStepper(200, 1); //   Molasses
Adafruit_StepperMotor *myMotor4 = AFMS_1.getStepper(200, 2); //   Egg
Adafruit_StepperMotor *myMotor5 = AFMS_2.getStepper(200, 1); //   Sugar
Adafruit_StepperMotor *myMotor6 = AFMS_2.getStepper(200, 2); //   Baking soda
Adafruit_StepperMotor *myMotor7 = AFMS_3.getStepper(200, 1); //   Chocolate chips
Adafruit_StepperMotor *myMotor8 = AFMS_3.getStepper(200, 2); //   Oats
Adafruit_StepperMotor *myMotor9 = AFMS_4.getStepper(200, 1); //   Flour
Adafruit_StepperMotor *myMotor10 = AFMS_4.getStepper(200, 2); //  Salt
Adafruit_StepperMotor *myMotor11 = AFMS_5.getStepper(200, 1); //  M&M's
Adafruit_DCMotor *myMotor12 = AFMS_5.getMotor(3); //  dc motor relay for flour agitator using port 3 (M3)


void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  establishContact(); // send a byte to establish contact until receiver responds 
  Serial.println("Program running");

  AFMS_0.begin();  // create with the default frequency 1.6KHz
  AFMS_1.begin();  // create with the default frequency 1.6KHz
  AFMS_2.begin();  // create with the default frequency 1.6KHz
  AFMS_3.begin();  // create with the default frequency 1.6KHz
  AFMS_4.begin();  // create with the default frequency 1.6KHz
  AFMS_5.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  //Define motor speeds globally
  myMotor2->setSpeed(60);   //  Vanilla
  myMotor3->setSpeed(60);   //  Molasses
  myMotor4->setSpeed(60);   //  Egg
  myMotor5->setSpeed(60);   //  Sugar
  myMotor6->setSpeed(30);   //  Baking Soda
  myMotor7->setSpeed(60);   //  Chocolate Chips
  myMotor8->setSpeed(60);   //  Oats
  myMotor9->setSpeed(60);   //  Flour
  myMotor10->setSpeed(60);  //  Salt
  myMotor11->setSpeed(60);  //  M&M's
  // DC motor speed (0 to 255) using PWM duty cycle.
  // This number does not control the motor speed, just the signal to the relay
  myMotor12->setSpeed(255);

  //Remove all power from the motors
  myMotor1->release();
  myMotor2->release();
  myMotor3->release();
  myMotor4->release();
  myMotor5->release();
  myMotor6->release();
  myMotor7->release();
  myMotor8->release();
  myMotor9->release();
  myMotor10->release();
  myMotor11->release();
  //myMotor12->release();

  // register serial commands that we can respond to. F("CommandName") is the name of the command and Cmd_FunctionToCall is the arduino function that will be called when the command is recieved
  SerialCommandHandler.AddCommand(F("Butter"), Cmd_Go1);
  SerialCommandHandler.AddCommand(F("Vanilla"), Cmd_Go2);
  SerialCommandHandler.AddCommand(F("Molasses"), Cmd_Go3);
  SerialCommandHandler.AddCommand(F("Egg"), Cmd_Go4);
  SerialCommandHandler.AddCommand(F("Sugar"), Cmd_Go5);
  SerialCommandHandler.AddCommand(F("BakingSoda"), Cmd_Go6);
  SerialCommandHandler.AddCommand(F("ChocolateChips"), Cmd_Go7);
  SerialCommandHandler.AddCommand(F("Oatmeal"), Cmd_Go8);
  SerialCommandHandler.AddCommand(F("Flour"), Cmd_Go9);
  SerialCommandHandler.AddCommand(F("Salt"), Cmd_Go10);
  SerialCommandHandler.AddCommand(F("MMs"), Cmd_Go11);
  //Commands for jogging dispenser up or down
  SerialCommandHandler.AddCommand(F("ButterUp"), Cmd_Go12);
  SerialCommandHandler.AddCommand(F("ButterDown"), Cmd_Go13);
  SerialCommandHandler.AddCommand(F("VanillaUp"), Cmd_Go14);
  SerialCommandHandler.AddCommand(F("VanillaDown"), Cmd_Go15);
  SerialCommandHandler.AddCommand(F("MolassesUp"), Cmd_Go16);
  SerialCommandHandler.AddCommand(F("MolassesDown"), Cmd_Go17);
  SerialCommandHandler.AddCommand(F("EggUp"), Cmd_Go18);
  SerialCommandHandler.AddCommand(F("EggDown"), Cmd_Go19);
  SerialCommandHandler.AddCommand(F("SugarUp"), Cmd_Go20);
  SerialCommandHandler.AddCommand(F("SugarDown"), Cmd_Go21);
  SerialCommandHandler.AddCommand(F("BakingSodaUp"), Cmd_Go22);
  SerialCommandHandler.AddCommand(F("BakingSodaDown"), Cmd_Go23);
  SerialCommandHandler.AddCommand(F("ChocolateChipsUp"), Cmd_Go24);
  SerialCommandHandler.AddCommand(F("ChocolateChipsDown"), Cmd_Go25);
  SerialCommandHandler.AddCommand(F("OatmealUp"), Cmd_Go26);
  SerialCommandHandler.AddCommand(F("OatmealDown"), Cmd_Go27);
  SerialCommandHandler.AddCommand(F("FlourUp"), Cmd_Go28);
  SerialCommandHandler.AddCommand(F("FlourDown"), Cmd_Go29);
  SerialCommandHandler.AddCommand(F("SaltUp"), Cmd_Go30);
  SerialCommandHandler.AddCommand(F("SaltDown"), Cmd_Go31);
  SerialCommandHandler.AddCommand(F("MMsUp"), Cmd_Go32);
  SerialCommandHandler.AddCommand(F("MMsDown"), Cmd_Go33);

}

void loop() {
  //this process always goes at the start of the loop function; it recieves characters from the serial port and calls the appropriate function whenever a command is called
  SerialCommandHandler.Process();
}

//create command functions for moving the dispenser with reference to the tracker
void Cmd_Go1(CommandParameter &Parameters) //Butter
{
  // step one revolution  in one direction:
  Steps = Parameters.NextParameterAsInteger() * 100; //calibrate the multiplication factor as necessary to match the dispensing scale shown on the interface
  Serial.print("Number of steps=");
  Serial.println(Steps);
  myMotor1->setSpeed(100);
  myMotor1->step(Steps, FORWARD, DOUBLE);
  Serial.println("Running butter dispenser");
  myMotor1->release(); //end function be removing power from the motor
}

void Cmd_Go2(CommandParameter &Parameters) //Vanilla
{
  // step one revolution  in one direction:
  Steps = Parameters.NextParameterAsInteger() * 20;
  Serial.print("Number of steps=");
  Serial.println(Steps);
  myMotor2->step(Steps, FORWARD, INTERLEAVE);
  Serial.println("Running vanilla dispenser");
  myMotor2->release(); //end function be removing power from the motor
}

void Cmd_Go3(CommandParameter &Parameters) //Molasses
{
  // step one revolution  in one direction:
  Steps = Parameters.NextParameterAsInteger() * 20;
  Serial.print("Number of steps=");
  Serial.println(Steps);
  myMotor3->step(Steps, FORWARD, INTERLEAVE);
  Serial.println("Running molasses dispenser");
  myMotor3->release(); //end function be removing power from the motor
}

void Cmd_Go4(CommandParameter &Parameters) //Egg
{
  // step one revolution  in one direction:
  Steps = Parameters.NextParameterAsInteger() * 20;
  Serial.print("Number of steps=");
  Serial.println(Steps);
  myMotor4->step(Steps, FORWARD, INTERLEAVE);
  Serial.println("Running egg dispenser");
  myMotor4->release(); //end function be removing power from the motor
}

void Cmd_Go5(CommandParameter &Parameters) //Sugar
{
  // step one revolution  in one direction:
  Steps = Parameters.NextParameterAsInteger() * 200;
  Serial.print("Number of steps=");
  Serial.println(Steps);
  myMotor5->step(Steps, FORWARD, DOUBLE);
  Serial.println("Running sugar dispenser");
  myMotor5->release(); //end function be removing power from the motor
}

void Cmd_Go6(CommandParameter &Parameters) //Baking Soda
{
  // step one revolution  in one direction:
  Steps = Parameters.NextParameterAsInteger() * 40;
  Serial.print("Number of steps=");
  Serial.println(Steps);
  Step2 = Steps;
  myMotor6->step(Steps, FORWARD, INTERLEAVE);
  delay(250);
  myMotor6->step(Step2, BACKWARD, INTERLEAVE);
  Serial.println("Running baking soda dispenser");
  myMotor6->release(); //end function be removing power from the motor
}

void Cmd_Go7(CommandParameter &Parameters) //Chocolate Chips
{
  // step one revolution  in one direction:
  Steps = Parameters.NextParameterAsInteger() * 140;
  Serial.print("Number of steps=");
  Serial.println(Steps);
  myMotor7->step(Steps, BACKWARD, INTERLEAVE);
  Serial.println("Running chocolate chips dispenser");
  myMotor7->release(); //end function be removing power from the motor
}

void Cmd_Go8(CommandParameter &Parameters) //Oatmeal
{
  // step one revolution  in one direction:
  Steps = Parameters.NextParameterAsInteger() * 140;
  Serial.print("Number of steps=");
  Serial.println(Steps);
  myMotor8->step(Steps, BACKWARD, INTERLEAVE);
  Serial.println("Running oatmeal dispenser");
  myMotor8->release(); //end function be removing power from the motor
}

void Cmd_Go9(CommandParameter &Parameters) //Flour
{
  // step one revolution  in one direction:
  Steps = Parameters.NextParameterAsInteger() * 140;
  Serial.print("Number of steps=");
  Serial.println(Steps);
  myMotor12->run(FORWARD); //Starting the agitator and delaying for one second
  delay(1000);
  myMotor9->step(Steps, FORWARD, INTERLEAVE); //Starting the flour dispenser
  Serial.println("Running flour dispenser and agitator");
  myMotor9->release(); //end function be removing power from the motor
  delay(2000); //Delaying 5 seconds before shutting off the agitator
  myMotor12->run(RELEASE); //end function be removing power from the motor
}

void Cmd_Go10(CommandParameter &Parameters) //Salt
{
  // step one revolution  in one direction:
  Steps = Parameters.NextParameterAsInteger() * 200;
  Serial.print("Number of steps=");
  Serial.println(Steps);
  myMotor10->step(Steps, FORWARD, DOUBLE);
  Serial.println("Running salt dispenser");
  myMotor10->release(); //end function be removing power from the motor
}

void Cmd_Go11(CommandParameter &Parameters) //MMs
{
  // step one revolution  in one direction:
  Steps = Parameters.NextParameterAsInteger() * 140;
  Serial.print("Number of steps=");
  Serial.println(Steps);
  myMotor11->step(Steps, FORWARD, INTERLEAVE);
  Serial.println("Running MMs dispenser");
  myMotor11->release(); //end function be removing power from the motor
}

//create command functions for moving the dispenser with reference to jog buttons

void Cmd_Go12(CommandParameter &Parameters)  // butter up
{
  myMotor1->setSpeed(1500);
  myMotor1->step(ButterJog, BACKWARD, DOUBLE);
  myMotor1->release(); //remove all power from the motor
}

void Cmd_Go13(CommandParameter &Parameters)  // butter down
{
  myMotor1->setSpeed(1500);
  myMotor1->step(ButterJog, FORWARD, DOUBLE);
  myMotor1->release(); //remove all power from the motor
}

void Cmd_Go14(CommandParameter &Parameters)  // vanilla up
{
  myMotor2->step(Jog, BACKWARD, DOUBLE);
  myMotor2->release(); //remove all power from the motor
}

void Cmd_Go15(CommandParameter &Parameters)  // vanilla down
{
  myMotor2->step(Jog, FORWARD, DOUBLE);
  myMotor2->release(); //remove all power from the motor
}

void Cmd_Go16(CommandParameter &Parameters)  // Molasses up
{
  myMotor3->step(Jog, BACKWARD, DOUBLE);
  myMotor3->release(); //remove all power from the motor
}

void Cmd_Go17(CommandParameter &Parameters)  // Molasses down
{
  myMotor3->step(Jog, FORWARD, DOUBLE);
  myMotor3->release(); //remove all power from the motor
}

void Cmd_Go18(CommandParameter &Parameters)  // Egg up
{
  myMotor4->step(Jog, BACKWARD, DOUBLE);
  myMotor4->release(); //remove all power from the motor
}

void Cmd_Go19(CommandParameter &Parameters)  // egg down
{
  myMotor4->step(Jog, FORWARD, DOUBLE);
  myMotor4->release(); //remove all power from the motor
}

void Cmd_Go20(CommandParameter &Parameters)  // Sugar CW
{
  //myMotor5->step(Jog, FORWARD, DOUBLE);
  //myMotor5->release(); //remove all power from the motor
}

void Cmd_Go21(CommandParameter &Parameters)  // Sugar CCW
{
  //myMotor5->step(Jog, BACKWARD, DOUBLE);
  //myMotor5->release(); //remove all power from the motor
}

void Cmd_Go22(CommandParameter &Parameters)  // Baking Soda up
{
  myMotor6->step(BakingSodaJog, FORWARD, DOUBLE);
  myMotor6->release(); //remove all power from the motor
}

void Cmd_Go23(CommandParameter &Parameters)  // Baking Soda down
{
  myMotor6->step(BakingSodaJog, BACKWARD, DOUBLE);
  myMotor6->release(); //remove all power from the motor
}

void Cmd_Go24(CommandParameter &Parameters)  // Choc Chips up
{
  myMotor7->step(Jog, BACKWARD, DOUBLE);
  myMotor7->release(); //remove all power from the motor
}

void Cmd_Go25(CommandParameter &Parameters)  // Choc Chips down
{
  myMotor7->step(Jog, FORWARD, DOUBLE);
  myMotor7->release(); //remove all power from the motor
}

void Cmd_Go26(CommandParameter &Parameters)  // Oats up
{
  myMotor8->step(Jog, BACKWARD, DOUBLE);
  myMotor8->release(); //remove all power from the motor
}

void Cmd_Go27(CommandParameter &Parameters)  // Oats down
{
  myMotor8->step(Jog, FORWARD, DOUBLE);
  myMotor8->release(); //remove all power from the motor
}

void Cmd_Go28(CommandParameter &Parameters)  // Flour up
{
  myMotor9->step(Jog, FORWARD, DOUBLE);
  myMotor9->release(); //remove all power from the motor
}

void Cmd_Go29(CommandParameter &Parameters)  // Flour down
{
  myMotor9->step(Jog, BACKWARD, DOUBLE);
  myMotor9->release(); //remove all power from the motor
}

void Cmd_Go30(CommandParameter &Parameters)  // Salt up
{
  //myMotor10->step(Jog, FORWARD, DOUBLE);
  //myMotor10->release(); //remove all power from the motor
}

void Cmd_Go31(CommandParameter &Parameters)  // Salt down
{
  //myMotor10->step(Jog, BACKWARD, DOUBLE);
  //myMotor10->release(); //remove all power from the motor
}

void Cmd_Go32(CommandParameter &Parameters)  // MMs up
{
  myMotor11->step(Jog, FORWARD, DOUBLE);
  myMotor11->release(); //remove all power from the motor
}

void Cmd_Go33(CommandParameter &Parameters)  // MMs down
{
  myMotor11->step(Jog, BACKWARD, DOUBLE);
  myMotor11->release(); //remove all power from the motor
}


void establishContact() {
  while (Serial.available() <= 0) {
  Serial.println("ping");   // send a "ping"
  delay(300);
  }
}
