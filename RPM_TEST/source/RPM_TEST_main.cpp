/*************************************************************
project:  PID AC Motor Speed Controller
author:  JR Bynum
description: Main Module - All control is done from here
*************************************************************/
#define  MAIN
#include "RPM_TEST_main.h"

// initialize the LCD library with the numbers of the interface pins
// initialized here ans declared extern in any other .cpp modules in which it is used
LiquidCrystal lcd(12, 11, 7, 8, 9, 10);

void setup() {                

//initialize global variables
init_global_vars();
//setup the pins to match the hardware
setup_inputs_outputs();
//setup and start 1ms timer - our heartbeat
setup_heartbeat_timer();
//initialized the LCD
init_lcd();


#ifdef DEBUG
   Serial.begin(115200);
  // Print a startup message
  Serial.println("I am Alive!");
    /* Configure the debug pin as output */  
  pinMode(debug_pin, OUTPUT);   
  
  #endif


}
//**********************************************************************************
// Main loop - all tasks are timed my the 1 ms timer interrupt 
// Tasks are setup using a task structure which includes a counter, a time, and a flag
// Current Tasks are:
//
// Temperature is calculated every 1 second
// RPM is calulated every 250 ms
//To do - 
// add PID
// add Triac Control
//***********************************************************************************

void loop() {


				//Check to see if its time to compute the temperature 
				//temp sensor is a LM135
				if(TEMPtask.timerfired == true )  //temperature measurement
				{
						TEMPtask.timerfired = false;				

						if(digitalRead(powerOn)) // power on switch is off - pin is high
						{
								lcd.setCursor(0,0);
								lcd.print ("Power Off");

						}
						lcd.setCursor(0,1);
						lcd.print("Temp: ");
						lcd.print(read_tempsensor());
				}
				//Check to see if its time to compute the RPM measurement
				//Sensor is an 
				if (RPMtask.timerfired == true)
				{
						RPMtask.timerfired = false;			
	
						if(!digitalRead(powerOn)) //power switch is in - pin is low
						{
								calc_rpm();
						}
				
				}
}




