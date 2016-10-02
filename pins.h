#ifndef PINS_H
#define PINS_H

#define setPin(Port, Bit, Val)    Port = Val ? Port | (1 << Bit) : Port & ~(1 << Bit);
//taken from http://www.electro-tech-online.com/threads/avr-gcc-any-comfortable-way-of-controlling-single-io-pins.121409/
#define readBit(b,n) ((b) & (1<<(n)))
//from http://www.electro-tech-online.com/threads/defining-and-using-bit-flags-in-c.140777/

//define gate switching pin macros
void PINS_init(void);

#endif
