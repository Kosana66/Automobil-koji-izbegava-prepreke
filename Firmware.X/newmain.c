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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************************************************/
/// Header files
/*************************************************************/
#include "timer_module/timer.h"
#include "adc_module/adc.h"
#include "uart_module/uart.h"
#include "pwm_module/pwm.h"
#include "digital_sensors/HCSR.h"

_FOSC(CSW_FSCM_OFF & XT_PLL4);
_FWDT(WDT_OFF);

/*************************************************************/
/// Macros
/*************************************************************/
#define SIZE_OF_WORD (6)
#define MAX_MEASURED_TIME (0xFFFF) // 2^16 because timer 4 and 5 are 16bit timers
#define SPEED_OF_SOUND (0.0343) // centimeters per microsecond

/*************************************************************/
/// Variables
/*************************************************************/
static unsigned int sharp_value, RsenseA_value, RsenseB_value;
static int us_counter, ms_counter;
static unsigned char tempRX1_debug, tempRX2_bluetooth;
static unsigned char word_Start[SIZE_OF_WORD];
static unsigned char position=0;
static unsigned int measured_distance_left = 0;
static unsigned int measured_distance_right = 0;


/*************************************************************/
/// Interrupt Service Routine(ISR)
/*************************************************************/

/// Interrupt Service Routine(ISR) for Timer1 - ms
void __attribute__ ((__interrupt__, no_auto_psv)) _T1Interrupt(void) 
{
    TMR1 = 0;
    ms_counter++;
    IFS0bits.T1IF = 0;     
}

/// Interrupt Service Routine(ISR) for Timer2 - us
void __attribute__ ((__interrupt__, no_auto_psv)) _T2Interrupt(void) 
{
    TMR2 = 0;
    us_counter++;
    IFS0bits.T2IF = 0;     
}

/// Interrupt Service Routine(ISR) for Timer3 - PWM
void __attribute__ ((__interrupt__, no_auto_psv)) _T3Interrupt(void) 
{
    TMR3 = 0;
    IFS0bits.T3IF = 0;     
}

/// Interrupt Service Routine(ISR) for Timer4
void __attribute__ ((__interrupt__, no_auto_psv)) _T4Interrupt(void) 
{
    TMR4 = 0;
    IFS1bits.T4IF = 0;     
}

/// Interrupt Service Routine(ISR) for Timer5
void __attribute__ ((__interrupt__, no_auto_psv)) _T5Interrupt(void) 
{
    TMR5 = 0;
    IFS1bits.T5IF = 0;     
}
/// Interrupt Service Routine(ISR) for AD conversion
void __attribute__ ((__interrupt__, no_auto_psv)) _ADCInterrupt(void) 
{
    sharp_value=ADCBUF0; // obstacle distance from the front side
    RsenseA_value=ADCBUF1;
    RsenseB_value=ADCBUF2;
   
    ADCON1bits.ADON = 0;
    IFS0bits.ADIF = 0;
} 

/// Interrupt Service Routine(ISR) for left HC-SR04 sensor
void __attribute__ ((__interrupt__, no_auto_psv)) _INT0Interrupt(void)
{     
    if(ECHO_LEFT == 1)  //  the value of the echo pin becomes 1 (the rising edge detected)
    {
        INTCON2bits.INT0EP = 1; //interrupt 0 is sensitive to the falling edge
        
        TMR4 = 0; // reset T4
        T4CONbits.TON = 1; // turn on T4, time measurement begins 
    }
    else           // the value of the echo pin becomes 0 (the falling edge detected)
    {
        T4CONbits.TON = 0;  // turn off T4, time measurement stops
        unsigned int measured_time_left = TMR4;
        if(measured_time_left >= MAX_MEASURED_TIME)
        {
            measured_time_left = MAX_MEASURED_TIME;
        }
        // measured_time_left/2 because the ultrasonic pulse travels to the obstacle and back
        measured_distance_left = (unsigned int)((measured_time_left/2)*SPEED_OF_SOUND);
        INTCON2bits.INT0EP = 0; //interrupt 0 is sensitive to the rising edge
    }
    IFS0bits.INT0IF = 0;
}

/// Interrupt Service Routine(ISR) for right HC-SR04 sensor
void __attribute__ ((__interrupt__, no_auto_psv)) _INT1Interrupt(void)
{     
    if(ECHO_RIGHT == 1)  //  the value of the echo pin becomes 1 (the rising edge detected)
    {
        INTCON2bits.INT1EP = 1; //interrupt 1 is sensitive to the falling edge
        
        TMR5 = 0; // reset T5
        T5CONbits.TON = 1; // turn on T5, time measurement begins 
    }
    else           // the value of the echo pin becomes 0 (the falling edge detected)
    {
        T5CONbits.TON = 0;  // turn off T5, time measurement stops
        unsigned int measured_time_right = TMR5;
        if(measured_time_right >= MAX_MEASURED_TIME)
        {
            measured_time_right = MAX_MEASURED_TIME;
        }
        // measured_time_right/2 because the ultrasonic pulse travels to the obstacle and back
        measured_distance_right = (unsigned int)((measured_time_right/2)*SPEED_OF_SOUND);
        INTCON2bits.INT1EP = 0; //interrupt 1 is sensitive to the rising edge
    }
    IFS1bits.INT1IF = 0;
}

/// Interrupt Service Routine(ISR) for UART1
void __attribute__ ((__interrupt__, no_auto_psv)) _U1RXInterrupt(void) 
{
    IFS0bits.U1RXIF = 0;
    tempRX1_debug=U1RXREG;
    WriteCharUART1(tempRX1_debug);
} 

/// Interrupt Service Routine(ISR) for UART2
void __attribute__ ((__interrupt__, no_auto_psv)) _U2RXInterrupt(void) 
{
    IFS1bits.U2RXIF = 0;
    tempRX2_bluetooth = U2RXREG;
    
    if(tempRX2_bluetooth != 0)
    {
        word_Start[position] = tempRX2_bluetooth;
        tempRX2_bluetooth = 0;

        if(position < SIZE_OF_WORD - 1)
        {
           position++;
           word_Start[position] = 0;
        }
        else position = 0;
    }
} 

/*************************************************************/
// FUNCTIONS FOR TIMERS
/*************************************************************/

/// Function for delay in miliseconds 
static void DelayMs (int vreme);
/// Function for delay in microseconds 
static void DelayUs (int vreme);

/*************************************************************/
// FUNCTIONS FOR MEASURING DISTANCE
/*************************************************************/

/// Function for measuring obstacle distance from the front side
static void MeasureFrontDistance();
/// Function for measuring obstacle distance from the left side
static void MeasureLeftDistance();
/// Function for measuring obstacle distance from the right side
static void MeasureRightDistance();


/* 
 * @brief - Function of main program
 * @param None
 * @return None
 */
int main(int argc, char** argv) {

    ///INITIALIZATION
    ConfigureADCPins();
    InitADC();
    Init_T1();
    Init_T2();
    Init_T3();
    Init_T4();
    Init_T5();
    InitUART1();
    InitUART2();
    InitPWM();
    ConfigureHCSR04Pins();
    InitHCSR04Sensors();
    memset(word_Start, 0, sizeof(word_Start));      
    
    /// ADCON1bits.ADON=1;
    WriteStringUART1("Init\n");
    
    
    while(1)
    {
       
        
        
       /* 
        while (word_Start[0]!='S' 
                || word_Start[1]!='T'
                || word_Start[2]!='A'
                || word_Start[3]!='R'
                || word_Start[4]!='T'
                || word_Start[5]!='\0'
                );
        memset(word_Start, 0, sizeof(word_Start));  
        position = 0;
        WriteStringUART2("Autic je pokrenut.");
        
        
        while(1)
        {
            ADCON1bits.ADON=1;
            WriteUART2dec2string(sharp_value);
            WriteStringUART2("----");
            DelayMs(1000);
        }
        
        
        
        while (word_Start[0]!='S' 
                || word_Start[1]!='T'
                || word_Start[2]!='O'
                || word_Start[3]!='P'
                || word_Start[4]!='\0'
                );
        memset(word_Start, 0, sizeof(word_Start));  
        position = 0;
        WriteStringUART2("Autic je zaustavljen.");   */
    }
    return (EXIT_SUCCESS);
}

/*************************************************************/
/// DEFINITION OF FUNCTIONS
/*************************************************************/

/* 
 * @brief - Function for delay in miliseconds
 * @param vreme - Duration of pause 
 * @return None
 */
static void DelayMs (int vreme)
{
    ms_counter = 0;
    T1CONbits.TON = 1;
    while(ms_counter < vreme);
    T1CONbits.TON = 0;
}

/* 
 * @brief - Function for delay in microseconds
 * @param vreme - Duration of pause 
 * @return None
 */
static void DelayUs (int vreme)
{
    us_counter = 0;
    T2CONbits.TON = 1;
    while(us_counter < vreme);
    T2CONbits.TON = 0;
}

/* 
 * @brief - Function for measuring obstacle distance from the front side
 * @param None
 * @return None
 */
static void MeasureFrontDistance()
{
    ADCON1bits.ADON=0;
    DelayMs(10);
    ADCON1bits.ADON=1;
}

/* 
 * @brief - Function for sending left trigger signal
 * @param None
 * @return None
 */
static void MeasureLeftDistance()
{
    // logical one lasts for 10us
    TRIG_LEFT = 1;
    DelayUs(10);
    TRIG_LEFT = 0;
}

/* 
 * @brief - Function for sending right trigger signal
 * @param None
 * @return None
 */
static void MeasureRightDistance()
{
    // logical one lasts for 10us
    TRIG_RIGHT = 1;
    DelayUs(10);
    TRIG_RIGHT = 0;
}