//USART_* functions taken from binaryupdates.com
#define F_CPU 1000000UL
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
 
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

#define INPUT_BUFFER_SIZE 20
#define OUTPUT_BUFFER_SIZE 20
 
void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_putstring(char* StringPtr);

char rx_buffer[INPUT_BUFFER_SIZE] = {'\n'}; //define recieve buffer
char *current_rxb;
char *current_txb;
char update_rxb = 0;
int i;

//define interrupt routine
//recieve complete
ISR(USART_RXC_vect)
{
  //get the recieved character from the buffer
  char a = UDR;

  //if character is a newline or terminated
  //or if the buffer is full, trigger buffer handling
  if (a == '\n' || a == '\r' || a == '\0' || *current_rxb){
    *current_rxb = a;
    current_rxb = rx_buffer;
    update_rxb = 1;

  }
  else{
    *current_rxb = a;
    current_rxb++;
  }
}

//transmit complete
ISR(USART_TXC_vect)
{
  //code
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

  }
}
/* Initialize USART */
void USART_init(void){

  sei(); //enable global interrupts
	
	UBRRH = (uint8_t)(BAUD_PRESCALLER>>8); //set baud rate
	UBRRL = (uint8_t)(BAUD_PRESCALLER);    
  UCSRA = (1<<UDRIE); //enable data registry empty
	/* UCSRB = (1<<RXEN)|(1<<TXEN) | (1<<RXCIE) | (1<<TXCIE);           //enable tx/rx and complete interrupts */
	UCSRB = (1<<RXEN)|(1<<TXEN) | (1<<RXCIE);           //enable tx/rx and complete interrupts TODO reenale txcie
  
	UCSRC = (1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL); //set up UaRtControlandStatusRegisterC
}
 
/* /1* Function to send byte/char *1/ */
/* void USART_send( unsigned char data){ */
	
/* 	while(!(UCSRA & (1<<UDRE))); //wait for empty transmit buffer */
/* 	UDR = data; //put data in udr */
/* } */
 
/* Send string */
void USART_putstring(char* S){
  current_txb = S;
  UCSRB |= (1<< UDRIE);
}

int  main()
{
  current_rxb = rx_buffer; //set rx buffer pointer
  
  //define LED outputs
  DDRA = 0x01;
  PORTA = 0x01;



  USART_init(); //init usart
  while(1){
    if (update_rxb){ //a string has been recieved, update the things
      update_rxb = 0; //don't do this again

      USART_putstring(rx_buffer);
      USART_putstring("\r\n");

      for (i = 0; i < INPUT_BUFFER_SIZE; i++){ 
        rx_buffer[i] = '\0';
      } //zero the rx_buffer
    }



    _delay_ms(1000);
    //toggle LED 
    PORTA ^= 0xFF;
  }

}
