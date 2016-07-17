#include "global.h"
#include "timers.h"
#include "uart.h"

#include <stdio.h>

int tmr_count;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TIMER2_OVF_vect
 *  Description:  interrupt routine triggered when timer2 overflows from the 
 *                32khz xtal, meaning one second has passed
 * =====================================================================================
 */
ISR(TIMER2_OVF_vect){
  //do async timeout things
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

  tmr_count = 0;
  TIMERS_start_async_timer(5);                  /* set the overflow time at 1s */
  /* TIMERS_start_io_timer(1); */
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TIMERS_set_async_compare_value
 *  Description:  Set the async counter compare value
 *                when the timer count is equal to this value, fire the compare 
 *                interrupt TIMER2_COMP 
 * =====================================================================================
 */
void TIMERS_set_async_compare_value(char comp){
  OCR2 = comp;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TIMERS_start_async_timer
 *  Description:  Starts the asychronous timer, with the prescaler set by the last three
 *                bits passed to the param timer. 
 *
 *                number prescale overflow time
 *                0      off
 *                1      1/1      7.8125ms
 *                2      1/8      62.5ms
 *                3      1/32     250ms
 *                4      1/64     500ms
 *                5      1/128    1m
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TIMERS_start_io_timer
 *  Description:  Like start_async_timer this starts the timer with the timer control
 *                reg set to the given paramater. the prescaler is set by the lower 
 *                three bits
 *
 *                number  prescale
 *                0       off
 *                1       1/1
 *                2       1/8
 *                3       1/64
 *                4       1/256
 *                5       1/1024
 *                6       clock on T1 pin, falling edge
 *                7       clock on T1 pin, rising edge
 *
 * =====================================================================================
 */
void TIMERS_start_io_timer(char timer){
  TCNT1 = 0;
  TCCR1B = timer;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TIMERS_stop_io_timer
 *  Description:  Stops the IO timer by setting TCCR1B = 0
 * =====================================================================================
 */
void TIMERS_stop_io_timer(void){
  TCCR1B = 0;

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TIMERS_get_io_count
 *  Description:  returns the current count from the io timer
 *                by returning the value of TCNT1
 * =====================================================================================
 */
int TIMERS_get_io_count(void){
  return TCNT1;
}

/*
 * in the case of prescaler 1, 7.8125ms, main osc should count 7812.5 ticks if accurate
 */
