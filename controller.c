#include "global.h"
#include "uart.h"
#include "network_parser.h"

 
int i, count;



int  main()
{
  sei();                                        //enable global interrupts
  
 
  USART_init();                                 //init usart
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
}
















