/*************************************************************
project: PID AC Motor Speed Controller
author: JR Bynum
description: Contains all the interrupt service routines
*************************************************************/
#include "RPM_TEST_main.h"


//*****************************************************************
// ISR are placed here
//*****************************************************************
//RPM Sensor interrupt - triggered on high transition
void rpm_function() {
			
			rpmcount++;
			//toggle pin 2 for testing
			debug();
}

//***************************************************************************************************************************
//Heartbeat 1 ms timer interrupt - uses timer 2 - this is the Tone interrupt for the Arduino Libaray so this function cannot be used
//***************************************************************************************************************************
/* 
 * Install the Interrupt Service Routine (ISR) for Timer2 overflow. 
 * This is normally done by writing the address of the ISR in the 
 * interrupt vector table but conveniently done by using ISR()  
* this is called every 1 ms*/  
ISR(TIMER2_OVF_vect) {  
		  /* Reload the timer */  
		  TCNT2 = tcnt2;  
		  
			//toggle pin 2 for testing
			//debug();

			//Heartbeat LED - 1 second toggle
			timer_toggle_led++;
			if(timer_toggle_led >= 1000 )
			{
				 timer_toggle_led=0;
				/* Write to a digital pin so that we can confirm our timer */  
				digitalWrite(13, toggleled == 0 ? HIGH : LOW);  
				toggleled = ~toggleled;  
			}
			//Temperature measurement timer
			TEMPtask.counter++;
			if(TEMPtask.counter  >= 	TEMPtask.timer)         //temperature measurement 
			{
						TEMPtask.timerfired = true;  //temperature measurement
						TEMPtask.counter = 0;
			}
			// RPM measurement timer
			RPMtask.counter++;
			if(RPMtask.counter  >= 	RPMtask.timer)         //RPM measurement 
			{
						RPMtask.timerfired = true;  //RPM measurement
						RPMtask.counter = 0;
			}


}  
  
