/*************************************************************
project:  PID AC Motor Speed Controller
author: JR Bynum
description: Diagnostics Functions - Functions for troubleshooting 
                             and checking the health of things.......
*************************************************************/

#include "RPM_TEST_main.h"

//Toggles a pin 2 to provide a debug toggle to scope
void debug(){

/* Write to a digital pin so that we can confirm our timer */  
  digitalWrite(2, toggle == 0 ? HIGH : LOW);  
  toggle = ~toggle;  


}