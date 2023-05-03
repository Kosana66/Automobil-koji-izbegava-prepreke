/* 
 * File:   newmain.c
 * Author: kosana
 *
 * Created on 03.01.2023., 23.18
 */

/*************************************************************/
/// Libraries
/*************************************************************/
#include <p30fxxxx.h>
#include <stdlib.h>

/*************************************************************/
/// Header files
/*************************************************************/
#include "timer_module/timer.h"
#include "adc_module/adc.h"
#include "uart_module/uart.h"

_FOSC(CSW_FSCM_OFF & XT_PLL4);
_FWDT(WDT_OFF);
_FGS(CODE_PROT_OFF);

/*************************************************************/
/// Macros
/*************************************************************/
#define TRIG_LEVO LATDbits.LATD2
#define ECHO_LEVO PORTDbits.RD8
#define TRIG_DESNO LATDbits.LATD9
#define ECHO_DESNO PORTAbits.RA11
#define SHARP LATBbits.LATB1

/*************************************************************/
/// Variables
/*************************************************************/
unsigned int sharp_value, RsenseA_value, RsenseB_value;
int time_counter1, time_counter2, time_counter3;
unsigned char tempRX1_Debug, tempRX2_Bluetooth;


/*************************************************************/
/// Interrupt Service Routine(ISR)
/*************************************************************/

/// Interrupt Service Routine(ISR) for Timer1
void __attribute__ ((__interrupt__)) _T1Interrupt(void) 
{
    TMR1 = 0;
    time_counter1++;
    IFS0bits.T1IF = 0;     
}

/// Interrupt Service Routine(ISR) for Timer2
void __attribute__ ((__interrupt__)) _T2Interrupt(void) 
{
    TMR2 = 0;
    time_counter2++;
    IFS0bits.T2IF = 0;     
}

/// Interrupt Service Routine(ISR) for Timer3
void __attribute__ ((__interrupt__)) _T3Interrupt(void) 
{
    TMR3 = 0;
    time_counter3++;
    IFS0bits.T3IF = 0;     
}

/// Interrupt Service Routine(ISR) for AD conversion
void __attribute__((__interrupt__)) _ADCInterrupt(void) 
{
    sharp_value=ADCBUF0;
    RsenseA_value=ADCBUF1;
    RsenseB_value=ADCBUF2;
   
    ADCON1bits.ADON=0;
    IFS0bits.ADIF = 0;
} 

/// Interrupt Service Routine(ISR) for UART1
void __attribute__((__interrupt__)) _U1RXInterrupt(void) 
{
    IFS0bits.U1RXIF = 0;
    tempRX1_Debug=U1RXREG;
} 

/// Interrupt Service Routine(ISR) for UART2
void __attribute__((__interrupt__)) _U2RXInterrupt(void) 
{
    IFS1bits.U2RXIF = 0;
    tempRX2_Bluetooth=U2RXREG;
} 

/*************************************************************/
// FUNKCIJE ZA TAJMERE
/*************************************************************/

/// Function for delay 
void Delay1 (int vreme);
/// Function for delay
void Delay2 (int vreme);
/// Function for delay
void Delay3 (int vreme);

/* 
 * @brief - Function of main program
 * @param None
 * @return None
 */
int main(int argc, char** argv) {

    ///INITIALIZATION
    ConfigureADCPins();
    ADCinit();
    Init_T1();
    Init_T2();
    Init_T3();
    InitUART1();
    InitUART2();
        
    /// ADCON1bits.ADON=1;
    
    
    while(1)
    {
        
                
        
            
    }
    return (EXIT_SUCCESS);
}

/*************************************************************/
/// DEFINITION OF FUNCTIONS
/*************************************************************/

/* 
 * @brief - Function for delay
 * @param vreme - Duration of pause 
 * @return None
 */
void Delay1 (int vreme)
{
    time_counter1 = 0;
    T1CONbits.TON = 1;
    while(time_counter1 < vreme);
    T1CONbits.TON = 0;
}

/* 
 * @brief - Function for delay
 * @param vreme - Duration of pause 
 * @return None
 */
void Delay2 (int vreme)
{
    time_counter2 = 0;
    T2CONbits.TON = 1;
    while(time_counter2 < vreme);
    T2CONbits.TON = 0;
}

/* 
 * @brief - Function for delay
 * @param vreme - Duration of pause 
 * @return None
 */
void Delay3 (int vreme)
{
    time_counter3 = 0;
    T3CONbits.TON = 1;
    while(time_counter3 < vreme);
    T3CONbits.TON = 0;
}
	