#include "global.h"
#include "timers.h"
#include "pins.h"

/*-----------------------------------------------------------------------------
 *  this should probably be a macro
 *-----------------------------------------------------------------------------*/


void PWM_set_half_pwm(int current, int pwm, int pwm_num){
  if (current < pwm){
    switch (pwm_num){
      case 0:
        AHI1(1);
        ALI1(1);
        break;

      case 1:
        BHI1(1);
        BLI1(1);
        break;

      case 2:
        AHI2(1);
        ALI2(1);
        break;

      case 3:
        BHI2(1);
        BLI2(1);
        break;
      }
    }
    else{
      switch(pwm_num){
        case 0:
          AHI1(0);
          ALI1(0);
          break;

        case 1:
          BHI1(0);
          BLI1(0);
          break;

        case 2:
          AHI2(0);
          ALI2(0);
          break;

        case 3:
          BHI2(0);
          BLI2(0);
          break;
    }
  }
}


void PWM_set_full_pwm(int current, int pwm, int pwm_num){
  if (current < pwm){
    switch (pwm_num){
      case 0:
        AHI1(1);
        ALI1(0);
        BHI1(0);
        BLI1(1);
        break;

      case 1:
        AHI2(1);
        ALI2(0);
        BHI2(0);
        BLI2(1);
        break;
      }
    }

    else{
      switch(pwm_num){
        case 0:
          AHI1(0);
          ALI1(1);
          BHI1(1);
          BLI1(0);
          break;

        case 1:
          AHI2(0);
          ALI2(1);
          BHI2(1);
          BLI2(0);
          break;
    }
  }
}
