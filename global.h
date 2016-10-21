#ifndef GLOBAL_H
#define GLOBAL_H

#define F_CPU 16000000UL
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
 
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

#define INPUT_BUFFER_SIZE 25

#endif
