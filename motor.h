#ifndef MOTOR_H
#define MOTOR_H

void MOTOR_init();
void MOTOR_INA(int val);
void MOTOR_INB(int val);

//set motor behaviors
void MOTOR_set_CW();
void MOTOR_set_CCW();
void MOTOR_set_break_VCC();
void MOTOR_set_break_GND();

#endif
