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

/// Function for setting duty cycle for PWM1
void DutyCyclePWM1(int duty_cycle);

/// Function for setting duty cycle for PWM2
void DutyCyclePWM2(int duty_cycle);

#endif	/* PWM_H */

