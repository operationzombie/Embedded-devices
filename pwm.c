#include "global.h"

//values are 0-25 for dutycycle at 600Hz
//with 0 being nothing, and 25 being 100%
//first argument is pin 9
//second argument is pin 10
void PWM_set(int duty_1, int duty_2){
  DDRB |= (1 << DDB1)|(1 << DDB2);
	// PB1 and PB2 is now an output

	ICR1 = 25;
	// set TOP to 180

	OCR1A = duty_1;
	// duty 177

	OCR1B = duty_2;
	// duty 177
	
	TCCR1A |= (1 << COM1A1)|(1 << COM1B1);
	// set none-inverting mode

	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12)|(1 << WGM13);
	// set Fast PWM mode using ICR1 as TOP
	
	TCCR1B |= (1 << CS12);
	// 256 presc}
}
