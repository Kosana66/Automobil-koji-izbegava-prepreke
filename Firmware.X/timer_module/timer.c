/* 
 * File:   timer.c
 * Author: kosana
 *
 * Created on 03.05.2023., 22.55
 */

#include <p30fxxxx.h>

/// Header file for AD conversion
#include "timer.h"

#define TMR1_period 10000   // 1/Fosc = 1/10000000 = 0.1us , 0.1us * 10000 = 1ms
#define TMR2_period 10  // 1/Fosc = 1/10000000 = 0.1us , 0.1us * 10 = 1us
#define TMR3_period 5000
#define TMR4_period 50000
#define TMR5_period 50000

/* 
 * @brief - Function for initializing Timer1
 * @param None
 * @return None
 */
void Init_T1(void)
{
    TMR1 = 0;
    PR1 = TMR1_period;
    T1CONbits.TCS = 0; // 0 = Internal clock (FOSC/4)
    IFS0bits.T1IF = 0; // clear timer1 interrupt flag
    IEC0bits.T1IE = 1; // enable timer1 interrupt
    T1CONbits.TON = 0; // Timer1 off 
}

/* 
 * @brief - Function for initializing Timer2
 * @param None
 * @return None
 */
void Init_T2(void)
{
    TMR2 = 0;
    PR2 = TMR2_period;
    T2CONbits.TCS = 0; // 0 = Internal clock (FOSC/4)
    IFS0bits.T2IF = 0; // clear timer2 interrupt flag
    IEC0bits.T2IE = 1; // enable timer2 interrupt
    T2CONbits.TON = 0; // Timer2 off 
}

/* 
 * @brief - Function for initializing Timer3
 * @param None
 * @return None
 */
void Init_T3(void)
{
    TMR3 = 0;
    PR3 = TMR3_period;
    T3CONbits.TCS = 0; // 0 = Internal clock (FOSC/4)
    IFS0bits.T3IF = 0; // clear timer3 interrupt flag
    IEC0bits.T3IE = 1; // enable timer3 interrupt
    T3CONbits.TON = 0; // Timer3 off 
}

/* 
 * @brief - Function for initializing Timer4
 * @param None
 * @return None
 */
void Init_T4(void)
{
    TMR4 = 0;
    PR4 = TMR4_period;
    T4CONbits.TCS = 0; // 0 = Internal clock (FOSC/4)
    IFS1bits.T4IF = 0; // clear timer4 interrupt flag
    IEC1bits.T4IE = 1; // enable timer4 interrupt
    T4CONbits.TON = 0; // Timer4 off 
}

/* 
 * @brief - Function for initializing Timer5
 * @param None
 * @return None
 */
void Init_T5(void)
{
    TMR5 = 0;
    PR5 = TMR5_period;
    T5CONbits.TCS = 0; // 0 = Internal clock (FOSC/4)
    IFS1bits.T5IF = 0; // clear timer5 interrupt flag
    IEC1bits.T5IE = 1; // enable timer5 interrupt
    T5CONbits.TON = 0; // Timer5 off 
}