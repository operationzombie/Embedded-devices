#include "global.h"
#include "pins.h"
#include "pwm.h"

void MOTOR_init(){
  //motor control pins:
  //digital 8 = PB0 = INB
  //digital 7 = PD7 = INA
  
  //define digital out for INA
  DDRB = 0x01;

  //define digital in for INB
  DDRD = 0x00 || (1 << 7);
}



void MOTOR_dir(int val){
  setPin(PORTB, 0, val);
}

void MOTOR_set_break(){
  PWM_disable();
}
