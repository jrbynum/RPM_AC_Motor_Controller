/*************************************************************
project: PID AC Motor Speed Controller
author: JR Bynum
description: Startup - contains all the initialization functions
*************************************************************/

#include "RPM_TEST_main.h"

extern LiquidCrystal lcd;

//initialize all variables to their proper conditions
void init_global_vars(){

			rpmcount = 0;
			rpm = 0;
			timeold = 0;

			 //software timers
			 timer_calc_rpm = 0;
			 timer_toggle_led = 0;
			 
			 /* Timer2 reload value, globally available */  
			tcnt2 = 0;  
			  
			/* Toggle HIGH or LOW digital write */  
			toggle = 0;  
			toggleled=0;  
			
			

}

//Setup the pins for inputs or outputs and attach interrupts if needed
void setup_inputs_outputs()
{
		  //Setup the Power On Switch
		  pinMode(powerOn, INPUT);
		  digitalWrite(powerOn,HIGH); // turn on pullup resistor 
			  
		  //setup led on pin 13 as an output
		  pinMode(13, OUTPUT);     
		  digitalWrite(13,LOW); // turn off pullup resistor 

		  //setup led on pin 2 as an output for debug
		  pinMode(2, OUTPUT);     
		  digitalWrite(2,LOW); // turn off pullup resistor 


		  //Setup the RPM Sensor
		  pinMode(rpm_sensor, INPUT);
		//  digitalWrite(rpm_sensor,LOW); // turn off pullup resistor - sensor idles low
		// attachInterrupt(1,rpm_function,RISING);
		  digitalWrite(rpm_sensor,LOW); // turn off pullup resistor - sensor idles low
		  attachInterrupt(1,rpm_function,RISING);

}

void setup_heartbeat_timer(){

		  /* First disable the timer overflow interrupt while we're configuring */  
		  TIMSK2 &= ~(1<<TOIE2);  
		  
		  /* Configure timer2 in normal mode (pure counting, no PWM etc.) */  
		  TCCR2A &= ~((1<<WGM21) | (1<<WGM20));  
		  TCCR2B &= ~(1<<WGM22);  
		  
		  /* Select clock source: internal I/O clock */  
		  ASSR &= ~(1<<AS2);  
		  
		  /* Disable Compare Match A interrupt enable (only want overflow) */  
		  TIMSK2 &= ~(1<<OCIE2A);  
		  
		  /* Now configure the prescaler to CPU clock divided by 128 */  
		  TCCR2B |= (1<<CS22)  | (1<<CS20); // Set bits  
		  TCCR2B &= ~(1<<CS21);             // Clear bit  
		  
		  /* We need to calculate a proper value to load the timer counter. 
		   * The following loads the value 131 into the Timer 2 counter register 
		   * The math behind this is: 
		   * (CPU frequency) / (prescaler value) = 125000 Hz = 8us. 
		   * (desired period) / 8us = 125. 
		   * MAX(uint8) + 1 - 125 = 131; 
		   */  
		  /* Save value globally for later reload in ISR */  
		  tcnt2 = 131;   
		  
		  /* Finally load end enable the timer */  
		  TCNT2 = tcnt2;  
		  TIMSK2 |= (1<<TOIE2);  

}

void init_lcd(){

			// set up the LCD's number of columns and rows: 
		  lcd.begin(16, 2);
		  // Print a message to the LCD.
		  lcd.print("RPM");

}

/* ------------- Operating system structure--------------------
struct opsys {
	
			bool timerfired;
			unsigned long timer;
			unsigned long counter;
			void * function;
  };
 */

void setup_operating_system(){

			RPMtask.timerfired = false;    //rpm measurement
			RPMtask.timer = 250;                 //rpm measurement - every 250 ms
			RPMtask.counter = 0;                 //rpm measurement - counter
			
			TEMPtask.timerfired = false;  //temperature measurement
			TEMPtask.timer = 1000;          //temperature measurement - every 1000 ms (1sec)
			TEMPtask.counter = 0;          //temperature measurement - counter

}