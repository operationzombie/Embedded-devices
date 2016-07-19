#include "global.h"

void PINS_init(void){
  //set input/output modes for pins
  DDRA = 0x80;                                  /* 0b10000000 */
  DDRB = 0x70;                                  /* 0b01110000 */
  DDRC = 0x3F;                                  /* 0b00111111 */
  DDRD = 0x4C;                                  /* 0b01001100 */
}
