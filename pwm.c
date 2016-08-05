#include "global.h"
#include "timers.h"
#include "pins.h"

/*-----------------------------------------------------------------------------
 *  this should probably be a macro
 *-----------------------------------------------------------------------------*/


void PWM_set_pin_status(int current, int pwm, volatile int port, int pin){
  if (current < pwm){
    setPin(port, pin, 1);
  }
  else{
    setPin(port, pin, 0);
  }
}
