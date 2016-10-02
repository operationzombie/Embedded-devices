#include "global.h"
#include "uart.h"
#include "pwm.h"
#include "pins.h"
#include "motor.h"
 
int i;

int  main()
{
  sei();                                        //enable global interrupts
  
  PINS_init();
  MOTOR_init();
  USART_init();                                 //init usart

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
    //values are 0-25 for dutycycle at 600Hz
    //first argument is pin 9
    //second argument is pin 10
    PWM_set(25,0);
    MOTOR_set_CW();
  }

}
