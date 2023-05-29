/* 
 * File:   pwm.h
 * Author: kosana
 *
 * Created on 29.05.2023., 19.41
 */

#ifndef PWM_H
#define	PWM_H

///library for MCU
#include <p30fxxxx.h>

/// Function for initializing PWM module
void InitPWM();

/// Function for setting duty cycle for PWM
void DutyCyclePWM(int duty_cycle);

#endif	/* PWM_H */

