#include "global.h"
#include "uart.h"

char rx_buffer[INPUT_BUFFER_SIZE] = {'\0'};     //define recieve buffer
char complete_buffer[INPUT_BUFFER_SIZE] ;       //define buffer for finished message
char *current_rxb;
char *current_txb;
char update_rxb = 0;
char currently_tx = 0;
int u;                                          //uart for loop counter

/*Prototypes */
void send_update();

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  USART_RXC_vect
 *  Description:  the interrupt routine fired when a character has been recieved
 * =====================================================================================
 */
ISR(USART_RX_vect)
{
  //get the recieved character from the buffer
  char a = UDR0;
  *current_rxb++ = a;
  //if character is a newline or terminated
  //or if the buffer is full, trigger buffer handling
  if (a == '\r' || a == '\0' || a == '\n' ||  (*current_rxb)){
    update_rxb = 1;
  }

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  USART_UDRE_vect
 *  Description:  the interrupt routine fired when a character has finished tx
 * =====================================================================================
 */
ISR(USART_UDRE_vect)
{
  //if we've got a valid character in the output buffer, send it
  if (*current_txb){
    UDR0 = *current_txb++;
  }
  else {
    //data done transmitting, disable tx interrupt
    UCSR0B &= ~(1 << UDRE0);
    currently_tx = 0;
  }
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  USART_init
 *  Description:  set all registers and initialize relevant variables to enable uart
 * =====================================================================================
 */
void USART_init(void){
  current_rxb = rx_buffer; //set rx buffer pointer
  
  UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8); //set baud rate
  UBRR0L = (uint8_t)(BAUD_PRESCALLER);    
  UCSR0A = (1<<UDRIE0); //enable data registry empty
  UCSR0B = (1<<RXEN0)|(1<<TXEN0) | (1<<RXCIE0);           //enable tx/rx and complete interrupts TODO reenale txcie
  
  //UCSR0C = (1<<UCSZ00)|(1<<UCSZ01); //set up UaRtControlandStatusRegisterC
    UCSR0C = ((0<<USBS0)|(1 << UCSZ01)|(1<<UCSZ00));  //ADDED UCSZ00
    sei();//ADDED
}
 
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  USART_putstring
 *  Description:  transmits a string via serial
 *
 *                Warning: if this is called when currently transmitting, the current 
 *                message pointer will be replkaced with this one, meaning the 
 *                message will not be properly transmitted
 * =====================================================================================
 */
void USART_putstring(char* S){
  current_txb = S;
  UCSR0B |= (1<< UDRIE0);
  currently_tx = 1;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  USART_get_tx_status
 *  Description:  getter function, reporting current status of transmission
 * =====================================================================================
 */
char USART_get_tx_status(void){
  return currently_tx;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  USART_need_rx_update
 *  Description:  getter function, reporting the current need for string recieve 
 *                handling
 * =====================================================================================
 */
char USART_need_rx_update(void){
  return update_rxb;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  USART_unset_rxb_update
 *  Description:  setter, unsets the need_rxb_update flag, indicating the recent rxb 
 *                action has been performed
 * =====================================================================================
 */
void USART_unset_rxb_update(void){
  update_rxb = 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  USART_copy_rxb
 *  Description:  copy the rx buffer to complete_buffer, useful if a buffer fills, or
 *                transmission completes, so prepare for new transmission
 * =====================================================================================
 */
void USART_copy_rxb(void){
  //copy the rx buffer, then zero it for incoming transmission
  for (u = 0; u < INPUT_BUFFER_SIZE; u++){
    complete_buffer[u] = rx_buffer[u]; 
    rx_buffer[u] = '\0'; 
  }
  current_rxb = rx_buffer; //reset the buffer pointer
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  USART_get_last_message
 *  Description:  getter, returning the last complete message recieved (or the rx_buffer
 *                when it filled)
 * =====================================================================================
 */
char* USART_get_last_message(void){
  return complete_buffer;
}


/*STUFF THAT IS PROBABLY GOING TO BREAK EVERYTHING*/

void USART_send( unsigned char data)
{
  //while the transmit buffer is not empty loop
  while(!(UCSR0A & (1<<UDRE0)));
  
  //when the buffer is empty write data to the transmitted  
  UDR0 = data;
}


