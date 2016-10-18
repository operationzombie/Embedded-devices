#include "global.h"
#include "pins.h"

//values are 0-25 for dutycycle at 600Hz
//with 0 being nothing, and 25 being 100%
//first argument is pin 9
//second argument is pin 10
void PWM_set(int duty_1){
  DDRB |= (1 << DDB1)|(1 << DDB2);
	// PB1 and PB2 is now an output

	ICR1 = 25;
	// set TOP to 180

	//specify dutycycle
	OCR1A = duty_1;
	
	TCCR1A |= (1 << COM1A1)|(1 << COM1B1);
	// set none-inverting mode

	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12)|(1 << WGM13);
	// set Fast PWM mode using ICR1 as TOP
	
	TCCR1B |= (1 << CS12);
	// 256 presc}
}

void PWM_disable(){
	//TODO: unset COM1A1 COM1A0 bits
	setPin(TCCR1A, 7, 0);
	setPin(TCCR1A, 6, 0);
}
