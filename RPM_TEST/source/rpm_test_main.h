//-------------------------------------------------------------------
#ifndef __rpm_test_main_H__
#define __rpm_test_main_H__
//-------------------------------------------------------------------
 
#include <arduino.h>
// include the library code:
#include <LiquidCrystal.h>

 
//-------------------------------------------------------------------
 
//-------------------------------------------------------------------
 
// Put yout declarations here
//#define DEBUG 1 // comment out to get rid of debuging code
 #define rpm_sensor 3 
 #define powerOn 4
 #define debug_pin 2
 #define NOISE 125
 #define RPMAVG 250
 #define TEMPSENSOR1 0
 
 struct opsys {
	
			bool timerfired;
			unsigned long timer;
			unsigned long counter;
  };
 
 //use EXTERN for global vaiable - must initialize them in init_vars function
 #ifdef MAIN
#define EXTERN /* nothing */
#else
#define EXTERN extern
#endif /* DEFINE_VARIABLES */
 
 //operating system stuff
 EXTERN opsys RPMtask;    //rpm measurement
 EXTERN opsys TEMPtask;  //temperature measurement
 
 EXTERN unsigned int rpmcount;
 EXTERN unsigned int rpm;
 EXTERN unsigned long timeold;
 
 
 //software timers
 EXTERN unsigned long  timer_calc_rpm;
 EXTERN volatile unsigned long timer_toggle_led;
 
 /* Timer2 reload value, globally available */  
EXTERN unsigned int tcnt2;  
  
/* Toggle HIGH or LOW digital write */  
EXTERN int toggle;  
EXTERN int toggleled;  

//EXTERN LiquidCrystal lcd;

//--------------------------------------------------------------------
//Functions declared outside of MAIN in another file
//--------------------------------------------------------------------
//defined in - diagnostics.cpp
extern void debug();
//defined in - startup.cpp
extern void init_global_vars();
extern  void setup_inputs_outputs();
extern void setup_heartbeat_timer();
extern void init_lcd();
extern void setup_operating_system();

//defined in - calculations.cpp
extern long calc_rpm();
extern float read_tempsensor();
//defined in isrs.cpp
extern void rpm_function() ;

//-------------------------------------------------------------------
//End Functions Declerations
//--------------------------------------------------------------------
 
//===================================================================
// -> DO NOT WRITE ANYTHING BETWEEN HERE...
// 		This section is reserved for automated code generation
// 		This process tries to detect all user-created
// 		functions in main_sketch.cpp, and inject their
// 		declarations into this file.
// 		If you do not want to use this automated process,
//		simply delete the lines below, with "&MM_DECLA" text
//===================================================================
//---- DO NOT DELETE THIS LINE -- @MM_DECLA_BEG@---------------------
void loop();
void setup();
//---- DO NOT DELETE THIS LINE -- @MM_DECLA_END@---------------------
// -> ...AND HERE. This space is reserved for automated code generation!
//===================================================================
 
 
//-------------------------------------------------------------------
#endif
//-------------------------------------------------------------------
 
