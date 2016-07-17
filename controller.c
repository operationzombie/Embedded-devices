#include "global.h"
#include "uart.h"
 
int i;

int  main()
{
  sei(); //enable global interrupts
  
  //define LED outputs for blinking
  DDRA = 0x01;
  PORTA = 0x01;

  USART_init(); //init usart
  while(1){
    if (USART_need_rx_update()){ //a string has been recieved, update the things
      USART_unset_rxb_update();
      USART_copy_rxb();

      //print the recieved message
      USART_putstring(USART_get_last_message());

      //delay while tx completes to print newline
      //WARNING: this is blocking, for testing only
      //must be removed when implementation of 
      //timing sensitive content in main loop added
      while (USART_get_tx_status()){
        _delay_ms(10);
      }

      USART_putstring("\r\n");
    }

    _delay_ms(1000);
    //toggle LED 
    PORTA ^= 0xFF;
  }

}
