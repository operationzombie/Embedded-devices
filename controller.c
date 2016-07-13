//USART_* functions taken from binaryupdates.com
#define F_CPU 1000000UL
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
 
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

#define INPUT_BUFFER_SIZE 20
 
void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_putstring(char* StringPtr);

char rx_buffer[INPUT_BUFFER_SIZE] = {'\0'}; //define recieve buffer
char complete_buffer[INPUT_BUFFER_SIZE] ; //define buffer for finished message
char *current_rxb;
char *current_txb;
char update_rxb = 0;
char currently_tx = 0;
int i;

//define interrupt routine
//recieve complete
ISR(USART_RXC_vect)
{
  //get the recieved character from the buffer
  char a = UDR;
  *current_rxb++ = a;
  //if character is a newline or terminated
  //or if the buffer is full, trigger buffer handling
  if (a == '\r' || a == '\0' || *current_rxb){
    update_rxb = 1;
  }

}

//transmit complete
ISR(USART_UDRE_vect)
{
  //if we've got a valid character in the output buffer, send it
  if (*current_txb){
    UDR = *current_txb++;
  }
  else {
    //data done transmitting, disable tx interrupt
    UCSRB &= ~(1 << UDRE);
    currently_tx = 0;
  }
}
/* Initialize USART */
void USART_init(void){
  sei(); //enable global interrupts
	
	UBRRH = (uint8_t)(BAUD_PRESCALLER>>8); //set baud rate
	UBRRL = (uint8_t)(BAUD_PRESCALLER);    
  UCSRA = (1<<UDRIE); //enable data registry empty
	UCSRB = (1<<RXEN)|(1<<TXEN) | (1<<RXCIE);           //enable tx/rx and complete interrupts TODO reenale txcie
  
	UCSRC = (1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL); //set up UaRtControlandStatusRegisterC
}
 
/* Send string */
//WARNING: if this is called when currently transmitting,
//the current message pointer will be replaced with this one
void USART_putstring(char* S){
  current_txb = S;
  UCSRB |= (1<< UDRIE);
  currently_tx = 1;
}

int  main()
{
  current_rxb = rx_buffer; //set rx buffer pointer
  
  //define LED outputs for blinking
  DDRA = 0x01;
  PORTA = 0x01;


  USART_init(); //init usart
  while(1){
    if (update_rxb){ //a string has been recieved, update the things
      update_rxb = 0; //don't do this again

      //copy the rx buffer, then zero it for incoming transmission
      for (i = 0; i < INPUT_BUFFER_SIZE; i++){
        complete_buffer[i] = rx_buffer[i]; 
        rx_buffer[i] = '\0'; 
      }
      current_rxb = rx_buffer; //reset the buffer pointer

      //print the recieved message
      USART_putstring(complete_buffer);

      //delay while tx completes to print newline
      //WARNING: this is blocking, for testing only
      //must be removed when implementation of 
      //timing sensitive content in main loop added
      while (currently_tx){
        _delay_ms(10);
      }

      USART_putstring("\r\n");

    }

    _delay_ms(1000);
    //toggle LED 
    PORTA ^= 0xFF;
  }

}
