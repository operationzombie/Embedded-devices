#ifndef PWM_H
#define PWM_H

#define PWM_calculate_timer1_ovf(cpu_freq, pwm_freq, resolution) (1/(pwm_freq*resolution))/(1/cpu_freq)

int PWM_set_half_pwm(int current, int pwm, int pwm_num);
int PWM_set_full_pwm(int current, int pwm, int pwm_num);

#endif
