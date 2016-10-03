#include "global.h"
#include "uart.h"
#include "timers.h"
#include "pins.h"
 
int i, count;

int  main()
{
  sei();                                        //enable global interrupts
  
 
  //define LED outputs for blinking
  LED(1);
  /* DDRA = 0x01; */
  /* PORTA = 0x01; */

  USART_init();                                 //init usart
  PINS_init();
  TIMERS_init_async_timer();                    /* init timers */

  while(1){
    count++;
    if (USART_need_rx_update()){                //a string has been recieved, update the things
      USART_unset_rxb_update();
      USART_copy_rxb();
      _delay_ms(100);
      i = parse_message(USART_get_last_message());
      _delay_ms(100);
    }    
    _delay_ms(100);
                           /* toggle LED */
  }

    _delay_ms(1000);
    if (readBit(PORTB, 4)){
      LED(0);
    }
    else{
      LED(1);
    }
  }
}
















