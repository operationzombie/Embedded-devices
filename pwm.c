#include "global.h"
#include "pins.h"

/*  
 *  Initializes hardware PWM module 1, putting the module into fast PWM mode 
 *  PWM module 1 is connected to pin 9 on the arduino
 *  
 *  @param duty_1
 *     an integer in the range 0-25, specifying the required dutycycle forthe pwm module 
 *
 *  @return 
 *     void
 *
*/
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

/*  
 *  Disables PWM module 1, shutting off PWM output
 *  
 *  @param 
 *     void
 *
 *  @return 
 *     void
 *
*/
void PWM_disable(){
	//TODO: unset COM1A1 COM1A0 bits
	setPin(TCCR1A, 7, 0);
	setPin(TCCR1A, 6, 0);
}
