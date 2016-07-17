#include "global.h"
#include "uart.h"

char rx_buffer[INPUT_BUFFER_SIZE] = {'\0'}; //define recieve buffer
char complete_buffer[INPUT_BUFFER_SIZE] ; //define buffer for finished message
char *current_rxb;
char *current_txb;
char update_rxb = 0;
char currently_tx = 0;
int u;

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
  current_rxb = rx_buffer; //set rx buffer pointer
	
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

char USART_get_tx_status(void){
  return currently_tx;
}

char USART_need_rx_update(void){
  return update_rxb;
}

void USART_unset_rxb_update(void){
  update_rxb = 0;
}

void USART_copy_rxb(void){
  //copy the rx buffer, then zero it for incoming transmission
  for (u = 0; u < INPUT_BUFFER_SIZE; u++){
    complete_buffer[u] = rx_buffer[u]; 
    rx_buffer[u] = '\0'; 
  }
  current_rxb = rx_buffer; //reset the buffer pointer
}

char* USART_get_last_message(void){
  return complete_buffer;
}
