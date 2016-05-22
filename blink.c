#include <avr/io.h>
#include <util/delay.h>

int  main()
{
//unsigned int i =0;
/* Configure the GPIO B0 bit direction register as output */
DDRA = 0x01;
PORTA = 0x01;


 
while(1)
{

PORTA ^= 0xFF;

_delay_ms(500);
}

/* End of Program */
}
