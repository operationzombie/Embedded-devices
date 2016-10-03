#include "global.h"
#include "uart.h"

 
int i, count;



int  main()
{
  sei();                                        //enable global interrupts
  
  //define LED outputs for blinking
  DDRB = 0x07; //define LED pins
  PORTB = 0x07; //pins set to high
  
  USART_init();                                 //init usart
  while(1){
    count++;
    if (USART_need_rx_update()){                //a string has been recieved, update the things
      USART_unset_rxb_update();
      USART_copy_rxb();
      _delay_ms(100);
      i = parse_message(USART_get_last_message());
      _delay_ms(100);
      if(i>0){
        USART_putstring("success");
        _delay_ms(100);
      }
          send_update();
      }
    
    _delay_ms(100);
                           /* toggle LED */
  }

}


//~ARIEL*1
//~ARIEL*2
//~ARIEL*0

//~BELLE*2
//~ARIEL*2
//~ARIEL*0

//~1~2~0
















