#include "global.h"
#include "uart.h"
#include "timers.h"
#include "pins.h"
#include <stdio.h>
 
int i;
unsigned long int cpu_freq = 1000000;
unsigned long int BAUDRATE = 19200;

int  main()
{
  sei();                                        //enable global interrupts
  
  LED(1);                                       /* turn led on */
  cpu_freq = TIMERS_get_current_freq();            /* get the cpu frequency, found from xtal/timers */

  USART_init(BAUDRATE, F_CPU);                  //init usart
  PINS_init();

  TIMERS_init_async_timer();                    /* init timers */

  while(1){
    if (USART_need_rx_update()){                //a string has been recieved, update the things
      USART_unset_rxb_update();
      USART_copy_rxb();

      //print the recieved message
      USART_putstring(USART_get_last_message()); /* transmit the last recieved message (uart echo) */

      //delay while tx completes to print newline
      //WARNING: this is blocking, for testing onlm
      //must be removed when implementation of 
      //timing sensitive content in main loop added
      while (USART_get_tx_status()){
        _delay_ms(10);
      }

      USART_putstring("\r\n");
    }

    _delay_ms(1000);

    if (readLED){
      LED(0);
    }
    else{
      LED(1);
    }
  }
}

