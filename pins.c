#include "global.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  PINS_init
 *  Description:  Sets the input/output mode for all ports, based on the eletrical 
 *                schematic
 * =====================================================================================
 */
void PINS_init(void){
  DDRB = 0x01;
  DDRC = 0x00;
  DDRD = 0x00 || (1 << 7);
}
