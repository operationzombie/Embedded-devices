#include "uart.h"
#include "global.h"
// dir    trigger
// 0      rise
// 1      fall
// 2      any
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

void INTS_disable_int0(void){
  EIMSK &= ~(1 << INT0);
}

void INTS_disable_int1(void){
  EIMSK &= ~(1 << INT1);
}

ISR (INT0_vect)
{
    /* interrupt code here */
  USART_putstring("int1 triggered \r\n");
  _delay_ms(20);
}


ISR (INT1_vect)
{
  USART_putstring("int2 triggered \r\n");
  _delay_ms(20);
    /* interrupt code here */
}
