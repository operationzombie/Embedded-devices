#include "uart.h"
#include "global.h"
#include "pwm.h"

/*  
 *  Initalizes external interrupt 0, which will be fired in one of three cases
 *  determined by the value given to trigger. The three cases are:
 *    * rising edge of logic level input
 *    * falling edge of logic level input
 *    * change of logic level input  
 *
 *  @param trigger
 *      specify under which conditions the interrupt should fire
 *      0 - trigger on rising edge of logic level input
 *      1 - trigger on falling edge of logic level input
 *      2 - trigger on change of logic level input
 *  
 *  @return 
 *
*/
void INTS_init_0(int trigger){
  EIMSK |= (1 << INT0);
  switch(trigger){
    case 0:
      EICRA |= (1 << ISC01) | (1 << ISC00);
      break;
    case 1:
      EICRA |= (1 << ISC01) ;
      EICRA &=  ~(1 << ISC00);
      break;
    case 2:
      EICRA |= (1 << ISC00) ;
      EICRA &=  ~(1 << ISC01);
      break;
  }
}


/*  
 *  Initalizes external interrupt 1, which will be fired in one of three cases
 *  determined by the value given to trigger. The three cases are:
 *    * rising edge of logic level input
 *    * falling edge of logic level input
 *    * change of logic level input  
 *
 *  @param trigger
 *      specify under which conditions the interrupt should fire
 *      0 - trigger on rising edge of logic level input
 *      1 - trigger on falling edge of logic level input
 *      2 - trigger on change of logic level input
 *  
 *  @return 
 *
*/
void INTS_init_1(int trigger){
  EIMSK |= (1 << INT1);
  switch(trigger){
    case 0:
      EICRA |= (1 << ISC11) | (1 << ISC10);
      break;
    case 1:
      EICRA |= (1 << ISC11) ;
      EICRA &=  ~(1 << ISC10);
      break;
    case 2:
      EICRA |= (1 << ISC10) ;
      EICRA &=  ~(1 << ISC11);
      break;
  }
}

/*  
 *  Disables interrupt 0
 *
 *  @param void
 *  
 *  @return 
 *
*/
void INTS_disable_int0(void){
  EIMSK &= ~(1 << INT0);
}

/*  
 *  Disables interrupt 1
 *
 *  @param void
 *  
 *  @return 
 *
*/
void INTS_disable_int1(void){
  EIMSK &= ~(1 << INT1);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  INT0_vect
 *  Description:  the interrupt routine fired when the interrupt has been changed.
 *                this interrupt will disable PWM output
 * =====================================================================================
 */
ISR (INT0_vect)
{
    PWM_disable();
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  INT1_vect
 *  Description:  the interrupt routine fired when the interrupt has been changed.
 *                this interrupt will disable PWM output
 * =====================================================================================
 */
ISR (INT1_vect)
{
    PWM_disable();
}
