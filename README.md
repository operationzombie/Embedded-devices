This branch is an offshoot of the main codebase, stripped down and modified to run on any atmega328p microprocessor.
Please note that this processor change has required some changes, so the only code that can be easily ported from the main branch is that which has been abstracted away from the hardware.

At the time of writing this document, the codebase consisted almost exclusively of the basic code needed to enable serial communication. 

In order to use the code as it exists, you'll need:
Make
Avr-gcc
avrdude

All of these can be found linked in the README.txt file in the 'toolchain' directory.
Please note that the READEME.txt in toolchain is intended for the main codebase, and as such, steps 0, 5-7 may be ommitted.

You need to modify the makefile to point to the COM port on which the arduino is connected. 
The line in questions reads like this:

PROGRAMMER\_ARGS = -P COM7    

which at the time of writing this document was line 28.

with this modification made, running "make" should build the project and "make flash" should upload the code to the arduino

The current baudrate is 9600, and is set in global.h
