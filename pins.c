#include "global.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  PINS_init
 *  Description:  Sets the input/output mode for all ports, based on the eletrical 
 *                schematic
 * =====================================================================================
 */
void PINS_init(void){
  DDRA = 0x80;                                  /* 0b10000000 */
  DDRB = 0x70;                                  /* 0b01110000 */
  DDRC = 0x3F;                                  /* 0b00111111 */
  DDRD = 0x4C;                                  /* 0b01001100 */
}
