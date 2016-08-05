#ifndef PWM_H
#define PWM_H

#define PWM_calculate_timer1_ovf(cpu_freq, pwm_freq, resolution) (1/(pwm_freq*resolution))/(1/cpu_freq)

int PWM_set_pin_status(int current, int max, int port, int pin);


#endif
