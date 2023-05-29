/* 
 * File:   pwm.c
 * Author: kosana
 *
 * Created on 29.05.2023., 19.50
 */

#include <p30fxxxx.h>

/// Header file for PWM
#include "pwm.h"
#include "../timer_module/timer.h"

/* 
 * @brief - Function for iniializing PWM module
 * @param None
 * @return None
 */
void InitPWM()
{
    //the PWM mode of of the output compare module without input fault protection
    OC1CONbits.OCM=0b110; 
    OC2CONbits.OCM=0b110; 
    // Timer 3 as the source for the output compare module
    OC1CONbits.OCTSEL = 1;   
    OC2CONbits.OCTSEL = 1; 
    //initial PWM duty cycle
    OC1R = 0;  //Output Compare 1 Register
    OC2R = 0;  //Output Compare 1 Register
    OC1RS = 300;   //Output Compare 1 Secondary Register
    OC2RS = 300;   //Output Compare 2 Secondary Register
    
    // turn on timer 3
    T3CONbits.TON = 1; 
}

/* 
 * @brief - Function for setting duty cycle for PWM
 * @param duty_cycle - The value from 0 to 100
 * @return None
 */
void DutyCyclePWM(int duty_cycle)
{
    // Calculate the duty cycle based on the given value from 0.0 to 1.0
    unsigned int pwm_value = (unsigned int)((duty_cycle/100) * TMR3_period);

    // Set the new duty cycle
    OC1RS = pwm_value;   
    OC2RS = pwm_value;
}