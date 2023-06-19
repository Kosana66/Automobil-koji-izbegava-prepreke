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
    TRISDbits.TRISD0 = 0;   // output pin ENA
    TRISDbits.TRISD1 = 0;   // output pin ENB
    
    //the PWM mode of of the output compare module without input fault protection
    OC1CONbits.OCM=0b110; 
    OC2CONbits.OCM=0b110; 
    // Timer 3 as the source for the output compare module
    OC1CONbits.OCTSEL = 1;   
    OC2CONbits.OCTSEL = 1; 
    //initial PWM duty cycle
    OC1R = 0;  //Output Compare 1 Register
    OC2R = 0;  //Output Compare 1 Register
    OC1RS = 250;   //Output Compare 1 Secondary Register
    OC2RS = 250;   //Output Compare 2 Secondary Register
    
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
    if(duty_cycle>=0 && duty_cycle<=100)
    {
        // Calculate the duty cycle based on the given value from 0.0 to 1.0
        float pwm_value = (float)duty_cycle * (TMR3_period-1) /100;

        // Set the new duty cycle
        OC1RS = (int)pwm_value;   
        OC2RS = (int)pwm_value;
    }
}