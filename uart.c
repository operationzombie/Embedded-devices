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
  if (a == '\r' || a == '\0' || a == '\n' || a=='#' || (*current_rxb)){
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
 *  sets all registers and calculates any values needed to initialize the UART module
 *  this should be called once during program setup, or whenever the baud rate needs to
 *  be updated. 
 *  
 *  @param void
 *
 *  @return 
 *
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
 *  takes a char array and will update the current_txb address from which 
 *  characters are transmitted, and begings transmission before setting the currently_tx
 *  flag which indicated that the system is currently transmitting data
 *
 *  Note, calling this function while trasmission is currently underway will 
 *  overwrite the currrent_txb value, meaning the previously transmitting string will 
 *  be lost. 
 *
 *  
 *  @param void
 *
 *  @return 
 *    currently_tx status, indicating if the system is transmitting or not
 *
*/
void USART_putstring(char* S){
  current_txb = S;
  UCSR0B |= (1<< UDRIE0);
  currently_tx = 1;
}


/*  
 *  returns the current state of the update_rxb flag
 *  
 *  @param void
 *
 *  @return 
 *    currently_tx status, indicating if the system is transmitting or not
 *
*/
char USART_get_tx_status(void){
  return currently_tx;
}


/*  
 *  returns the current state of the update_rxb flag
 *  
 *  @param void
 *
 *  @return 
 *    update_rxb status indicating if the system needs to handle recieved input
 *
*/
char USART_need_rx_update(void){
  return update_rxb;
}

/*  
 *  Unsets the need_rxb_update flag, which signals a recieve operation has completed
 *  and that the main loop should check the latest message buffer
 *  
 *  @param void
 *
 *  @return 
 *
*/
void USART_unset_rxb_update(void){
  update_rxb = 0;
}

/*  
 *  copies the contents of the input buffer into the complete message buffer
 *  this should be called when one of seveal recieve cases have been met:
 *    * a newline character was recieved
 *    * an end of string character was recieved
 *    * the recieve buffer is full
 *  
 *  @param void
 *
 *  @return 
 *
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
 *  returns a buffer containing the last complete message
 *  recieved by the UART module
 *  
 *  @param void
 *
 *  @return 
 *      pointer to the character array buffer containing the 
 *      last recieved message
*/
char* USART_get_last_message(void){
  return complete_buffer;
}



/*  
 *  Send a single character out the UART module  
 *  
 *  @param data
 *      a single character to be transmitted
 *      
 *
 *  @return 
 *      void
*/
void USART_send( unsigned char data)
{
  //while the transmit buffer is not empty loop
  while(!(UCSR0A & (1<<UDRE0)));
  
  //when the buffer is empty write data to the transmitted  
  UDR0 = data;
}


