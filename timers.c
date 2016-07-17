#include "global.h"
#include "timers.h"
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
  //
  USART_putstring("1 second\r\n");
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TIMERS_init_async_timer
 *  Description:  Initializes the async timer
 * =====================================================================================
 */
void TIMERS_init_async_timer(void){
  USART_putstring("Initiating timers\n");
  ASSR |= (1 << AS2);                           /* set timer 2 input from tosc */
  TIMSK |= (1 << TOIE2);                        /* enable overflow interrupt */
/*TIMSK |= (1 << OCIE2);                        /1* enable output compare interrupt *1/ */

  /* TCCR2 |= (1 << CS22) | (1 << CS20);           /1* set prescaler to 128, so overflow 1/second *1/ */
  /* TCCR2 |= (1 << CS22)                          /1* set prescaler to 64, so overflow 2/second *1/ */
  /* TCCR2 |= (1 << CS20)                          /1* prescaler 1 = 7.8125ms *1/ */
  TIMERS_start_async_timer(5);
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TIMERS_start_async_timer
 *  Description:  Starts the asychronous timer, with the prescaler set by the last three
 *                bits passed to the param timer. 
 *
 *                number prescale overflow time
 *                1      1/1      7.8125ms
 *                2      1/8      62.5ms
 *                3      1/32     250ms
 *                4      1/64     500ms
 *                5      1/128    1s
 *                6      1/256    2s
 *                7      1/1024   8s
 *
 * =====================================================================================
 */
void TIMERS_start_async_timer(char timer){
  TCNT2 = 0;                                    /* reset the timer value */
  TCCR2 = timer;                               /* set the clock source to the given value */
}

void TIMERS_stop_async_timer(void){
  TCCR2 = 0; //remove clock source from the timer
}


void TIMERS_init_io_timer(void){

}

void TIMERS_start_io_timer(char timer){

}

void TIMERS_stop_io_timer(void){

}

/*
 * in the case of prescaler 1, 7.8125ms, main osc should count 7812.5 ticks if accurate
 */
