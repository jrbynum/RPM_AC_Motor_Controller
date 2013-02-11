/********************************************************************
project: PID AC Motor Speed Controller
author: JR Bynum
description: Calculations Module - all computations functions are here
********************************************************************/

#include "RPM_TEST_main.h"

extern LiquidCrystal lcd;

//RPM Calculation routine
long  calc_rpm(){

//			noInterrupts();
			if(rpmcount >= RPMAVG)
			{
			          detachInterrupt(1);
			
						unsigned long time = millis() - timeold; //get the current time in milliseconds
						float time_in_sec = (float)time / 1000;  //convert to seconds
//						float impuls_time = ((float)rpmcount / time_in_sec) / 4.0; // convert the counts to seconds
						float impuls_time = ((float)rpmcount / time_in_sec)  / 2.0; // convert the counts to seconds
						rpm = (int) impuls_time  * 60;   //compute rpm
#ifdef DEBUG				
						Serial.print("Time: ");
						Serial.print(time );
						Serial.print("\n");

						Serial.print("Impuls Time: ");
						Serial.print( impuls_time);
						Serial.print("\n");
						
						Serial.print("RPM Count: ");
						Serial.print(rpmcount);
						Serial.print("\n");
						Serial.print("\n");
						Serial.print("\n");
						
#endif
					rpmcount = 0; //reset rpm counter
					timer_calc_rpm = 0;
					timeold = millis(); //set new time
		
						
						if (rpm < 10000)
						{
									lcd.setCursor(0,0);
									lcd.print("RPM: ");
									lcd.setCursor(4,0);
									lcd.print(" ");
									lcd.setCursor(5,0);
									lcd.print (rpm);
									
						}
						else
						{
									lcd.setCursor(0,0);
									lcd.print("RPM: ");
									lcd.setCursor(4,0);
									lcd.print (rpm);
									
						}
						
                        attachInterrupt(1,rpm_function,FALLING);
						
			}
			//interrupts();
			return rpm;
// end calc rpm
}

float read_tempsensor(){

			float tempc;
			
			tempc = ((5.0 * analogRead(TEMPSENSOR1) * 100) / 1024.0) - 273.15;
			
			return tempc;
}