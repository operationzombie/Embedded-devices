#define setPin(Port, Bit, Val)    Port = Val ? Port | (1 << Bit) : Port & ~(1 << Bit);
//taken from http://www.electro-tech-online.com/threads/avr-gcc-any-comfortable-way-of-controlling-single-io-pins.121409/
#define readBit(b,n) ((b) & (1<<(n)))
//from http://www.electro-tech-online.com/threads/defining-and-using-bit-flags-in-c.140777/

//define gate switching pin macros
#define AHI1(x) setPin(PORTC, 0, x);
#define ALI1(x) setPin(PORTC, 1, x);
#define BHI1(x) setPin(PORTC, 2, x);
#define BLI1(x) setPin(PORTC, 3, x);
#define AHI2(x) setPin(PORTC, 4, x);
#define ALI2(x) setPin(PORTC, 5, x);

#define BHI2(x) setPin(PORTD, 6, x);

#define BLI2(x) setPin(PORTA, 7, x);

#define DIS1(x) setPin(PORTB, 5, x);
#define DIS2(x) setPin(PORTB, 6, x);

//general macros
#define LED(x) setPin(PORTB, 4, x);

//define xbee pin macros
#define RTS(x) setPin(PORTD, 2, x);
#define CTS(x) setPin(PORTD, 3, x);
#define readRTS readBit(PORTD, 2);
#define readCTS readBit(PORTD, 3);
#define XSleep(x) setPin(PORTD, 4, x);

void PINS_init(void);
