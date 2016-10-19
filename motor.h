#ifndef MOTOR_H
#define MOTOR_H

void MOTOR_init();
void MOTOR_dir(int val);

//set motor behaviors
void MOTOR_set_CW();
void MOTOR_set_CCW();
void MOTOR_set_break();

#endif
