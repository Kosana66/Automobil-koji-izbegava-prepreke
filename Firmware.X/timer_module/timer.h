/* 
 * File:   timer.h
 * Author: kosana
 *
 * Created on 03.05.2023., 22.49
 */

#ifndef TIMER_H
#define	TIMER_H

///library for MCU
#include <p30fxxxx.h>

#define TMR1_period 10000   // Tosc = 1/Fosc = 1/10000000 = 0.1us , 0.1us * 10000 = 1ms
#define TMR2_period 10      // Tosc = 1/Fosc = 1/10000000 = 0.1us , 0.1us * 10 = 1us
#define TMR3_period 500    // Tpwm = (PR3 + 1) * 4 * Tosc * Prescale_Value, Prescale_Value = 1
#define TMR4_period 10
#define TMR5_period 10

/// Function for initializing Timer1
void Init_T1(void);

/// Function for initializing Timer2
void Init_T2(void);

/// Function for initializing Timer3
void Init_T3(void);

/// Function for initializing Timer4
void Init_T4(void);

/// Function for initializing Timer5
void Init_T5(void);

#endif	/* TIMER_H */




