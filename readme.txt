RPM AC Motor Controller

This is an Arduino based motor controller that uses a reflective optical sensor to calculate rpm and an LM135
to compute temperature. It uses the PID library to compute feedback. RPM and Temperature are displayed on an LCD. 

A zero crossing circuit and triac are used to control the set RPM which is based upon a 10K pot. The circuit 
can also be controlled using a pwm input. This input could be used from Mach3.

More to follow....

Rusty Bynum
jrbynum@shaw.ca