#include "global.h"
#include "uart.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TIMER2_OVF_vect
 *  Description:  interrupt routine triggered when timer2 overflows from the 
 *                32khz xtal, meaning one second has passed
 * =====================================================================================
 */
ISR(TIMER2_OVF_vect){
  //do regular thinger when overflow
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TIMER2_COMP_vect
 *  Description:  the timer 2 count regester TCNT2 matched the value in the 
 *                output compare register OCR2
 * =====================================================================================
 */
ISR(TIMER2_COMP_vect){

}

void TIMERS_init_async_timer(void);

void TIMERS_init_async_timer(void){
  USART_putstring("Initiating timers\n");
  ASSR |= (1 << AS2);                           /* set timer 2 input from tosc */
  TIMSK |= (1 << TOIE2);                        /* enable overflow interrupt */
/*TIMSK |= (1 << OCIE2);                        /1* enable output compare interrupt *1/ */

  TCCR2 |= (1 << CS22) | (1 << CS20);           /* set prescaler to 128, so overflow 1/second */
  /* TCCR2 |= (1 << CS22)                          /1* set prescaler to 64, so overflow 2/second *1/ */
  /* TCCR2 |= (1 << CS20)                          /1* prescaler 1 = 7.8125ms *1/ */

}
