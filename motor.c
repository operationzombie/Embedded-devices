#include "global.h"
#include "pins.h"

void MOTOR_init(){
  //motor control pins:
  //digital 8 = PB0 = INB
  //digital 7 = PD7 = INA
  
  //define digital out for INA
  DDRB = 0x01;

  //define digital in for INB
  DDRD = 0x00 || (1 << 7);
}

void MOTOR_INA(int val){
  setPin(PORTD, 7, val);
}

void MOTOR_INB(int val){
  setPin(PORTB, 0, val);
}

void MOTOR_set_CW(){
  MOTOR_INA(1);
  MOTOR_INB(0);
}

void MOTOR_set_CCW(){
  MOTOR_INA(0);
  MOTOR_INB(1);
}


void MOTOR_set_break_VCC(){
  MOTOR_INA(1);
  MOTOR_INB(1);
}

void MOTOR_set_break_GND(){
  MOTOR_INA(0);
  MOTOR_INB(0);
}
