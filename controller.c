#include "global.h"
#include "uart.h"
#include "pwm.h"
#include "pins.h"
#include "motor.h"
#include "stdio.h"
#include "network_parser.h"

 
int i, count;
int speed;
int dir;

char buf[INPUT_BUFFER_SIZE];

  /*
  |===========================|
  |          pinmap           |
  |===========================|
  | pin  | port |   function  |
  | 0    | PD0  |   RX        |
  | 1    | PD1  |   TX        |
  | 2    | PD2  |   Int0      |
  | 3    | PD3  |   Int1      |
  | 8    | PB0  |   DIR       |
  | 9    | PB1  |   PWM1      |
  | 10   | PB2  |   PWM2      |
  | 13   | PB5  |   LED       |
  |===========================|
  */
  
int  main()
{
  sei();                                        //enable global interrupts

  DDRB = 0x00;
  DDRC = 0x00;
  DDRD = 0x00; 
  setPin(DDRB, 0,1); //pin 8  - DIR
  setPin(DDRB, 1,1); //pin 9  - PWM1
  setPin(DDRB, 2,1); //pin 10 - PWM2
  setPin(DDRB, 5,1); //pin 13 - LED
 
  USART_init();                                 //init usart
  USART_unset_rxb_update();                     //ensure we don't end up in rx_update loop

  //values are 0-25 for dutycycle at 600Hz
  //first argument is pin 9
  //second argument is pin 10
  
  //INTS_init_0(2);                               //enable interrupt 0, on change
  //INTS_init_1(2);                               //enable interrupt 1, on change

  while(1){
    count++;    
    _delay_ms(30);
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
    //read pin value, write the value back to serial
    //sprintf(buf,"pin11: %d\r\n",readBit(PIND,2)); //read the value from pin 11, write to serial
    //USART_putstring(buf);
    //_delay_ms(1000);
}
















