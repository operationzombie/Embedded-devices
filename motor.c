#include "global.h"
#include "pins.h"
#include "pwm.h"

/*  
 *  sets all relevant registers to ensure the relevant motor pins are set to output 
 *  
 *  @param void
 *
 *  @return 
 *
*/
void MOTOR_init(){
  //motor control pins:
  //digital 8 = PB0 = INB
  //digital 7 = PD7 = INA
  
  //define digital out for INA
  DDRB = 0x01;

  //define digital in for INB
  DDRD = 0x00 || (1 << 7);
}



/*  
 *  sets the direction in which the motor will turn
 *  
 *  @param val
 *    0 - clockwise
 *    1 - counter clockwise
 *
 *  @return 
 *
*/
void MOTOR_dir(int val){
  setPin(PORTB, 0, val);
}


/*  
 *  disables the motor output, placing the motor into brake state
 *  
 *  @param void
 *
 *  @return 
 *
*/
void MOTOR_set_break(){
  PWM_disable();
}
