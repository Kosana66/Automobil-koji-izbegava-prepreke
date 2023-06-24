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
#include "motor_module/motor.h"

_FOSC(CSW_FSCM_OFF & XT_PLL4);
_FWDT(WDT_OFF);

/*************************************************************/
/// Macros
/*************************************************************/
#define SIZE_OF_WORD (6)
#define SPEED_OF_SOUND (0.0343) // centimeters per microsecond
#define INSTRUCTION_CLOCK_PERIOD (0.1) // microseconds

/*************************************************************/
/// Variables
/*************************************************************/
static unsigned int sharp_value;
static int us_counter, ms_counter;
static unsigned char tempRX1_debug, tempRX2_bluetooth;
static unsigned char word_start[SIZE_OF_WORD];
static unsigned char position_UART2=0;
static int duty_cycle_entered1;
static int duty_cycle_entered2;
static float measured_distance_left = 0;
static float measured_distance_right = 0;
static unsigned char time_overflow_left=0;
static unsigned char time_overflow_right=0;


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

/// Interrupt Service Routine(ISR) for Timer4 - left position sensor
void __attribute__ ((__interrupt__, no_auto_psv)) _T4Interrupt(void) 
{
    TMR4 = 0;
    ECHO_LEFT = 0;
    time_overflow_left = 1;
    IFS1bits.T4IF = 0;     
}

/// Interrupt Service Routine(ISR) for Timer5 - right position sensor
void __attribute__ ((__interrupt__, no_auto_psv)) _T5Interrupt(void) 
{
    TMR5 = 0;
    ECHO_RIGHT = 0;  
    time_overflow_right = 1;
    IFS1bits.T5IF = 0;     
}

/// Interrupt Service Routine(ISR) for AD conversion - front position sensor
void __attribute__ ((__interrupt__, no_auto_psv)) _ADCInterrupt(void) 
{
    sharp_value=ADCBUF0; // obstacle distance from the front side
   
    ADCON1bits.ADON = 0;
    IFS0bits.ADIF = 0;
} 

/// Interrupt Service Routine(ISR) for UART1
void __attribute__ ((__interrupt__, no_auto_psv)) _U1RXInterrupt(void) 
{
    IFS0bits.U1RXIF = 0;
    tempRX1_debug=U1RXREG;
} 

/// Interrupt Service Routine(ISR) for UART2
void __attribute__ ((__interrupt__, no_auto_psv)) _U2RXInterrupt(void) 
{
    IFS1bits.U2RXIF = 0;
    tempRX2_bluetooth = U2RXREG;
    
    if(tempRX2_bluetooth != 0)
    {
        word_start[position_UART2] = tempRX2_bluetooth;
        tempRX2_bluetooth = 0;

        if(position_UART2 < SIZE_OF_WORD - 1)
        {
           position_UART2++;
           word_start[position_UART2] = 0;
        }
        else position_UART2 = 0;
    }
} 

/*************************************************************/
// FUNCTIONS FOR DELAYS
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

/*************************************************************/
// FUNCTIONS FOR INCREASING/DECREASING DUTY CYCLE
/*************************************************************/

/// Function for increasing/decreasing duty cycle for motors
static void ChangeDutyCycle();

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
    ConfigureMotorsPins(); 
    duty_cycle_entered1 = 75;
    DutyCyclePWM1(duty_cycle_entered1);
    duty_cycle_entered2 = 78;
    DutyCyclePWM2(duty_cycle_entered2);
    
    TRISBbits.TRISB8 = 0;
    ADPCFGbits.PCFG8 = 1;
    LATBbits.LATB8 = 1;
    
    memset(word_start, 0, sizeof(word_start));  
    position_UART2 = 0;
    WriteStringUART2("Write START.");
    WriteCharUART2(13);
    while (word_start[0]!='S' 
        || word_start[1]!='T'
        || word_start[2]!='A'
        || word_start[3]!='R'
        || word_start[4]!='T'
        || word_start[5]!='\0'
    );
    WriteStringUART2("The car is started.");
    WriteCharUART2(13);

    while(1)
    {    
        LATBbits.LATB8 = ~LATBbits.LATB8;
        
        /// algorithm of movement
        DriveForward();  
        MeasureFrontDistance();
        if(sharp_value > 680)   //ADC=680 if distance=15cm
        {
            StopMotors();
            DelayMs(300);
            MeasureLeftDistance();
            if(measured_distance_left > 20)     // the left sensor is 5cm away from the tank's track
            {
                //  Turn left if you have a front obstacle and no left obstacle
                TurnLeft();
                DelayMs(1300);
                StopMotors();
                DelayMs(300);
            }
            else
            {
                MeasureRightDistance();
                if(measured_distance_right > 21) // the right sensor is 6cm away from the tank's track
                {
                    //  Turn left if you have a front and left obstacle and no right obstacle
                    TurnRight();
                    DelayMs(1300);
                    StopMotors();
                    DelayMs(300);
                }
                else
                {
                    //  Stop if you have a front, left and right obstacle
                    StopMotors();
                    while(1);
                }
            }
        }
        else
        {
            MeasureLeftDistance();
            while(measured_distance_left < 20)
            {
                StopMotors();
                DelayMs(300);
                TurnRight();
                DelayMs(80);
                MeasureLeftDistance();
                if(measured_distance_left >= 20)
                {
                    StopMotors();
                    DelayMs(300);
                    DriveForward();
                }
            }
            MeasureRightDistance();
            while(measured_distance_right < 21)
            {
                StopMotors();
                DelayMs(300);
                TurnLeft();
                DelayMs(80);
                MeasureRightDistance();
                if(measured_distance_right >= 21)
                {
                    StopMotors();
                    DelayMs(300);
                    DriveForward();
                }
            }
        }
        ChangeDutyCycle();
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
    ADCON1bits.ADON=1;
    DelayMs(10);
    ADCON1bits.ADON=0;
}

/* 
 * @brief - Function for sending left trigger signal
 * @param None
 * @return measured_distance_left - Measured distance between left sensor and obstacle
 */
static void MeasureLeftDistance()
{
    // logical one lasts for 10us
    TRIG_LEFT = 1;
    DelayUs(3); //  3 instead of 10 to make logical one lasts for 10us
    TRIG_LEFT = 0;
    DelayUs(3);
    while(!ECHO_LEFT); //  the value of the echo pin becomes 1 (the rising edge detected)
    TMR4 = 0; // reset T4
    IFS1bits.T4IF = 0;
    T4CONbits.TON = 1; // turn on T4, time measurement begins 
    while(ECHO_LEFT);        // the value of the echo pin becomes 0 (the falling edge detected)
    T4CONbits.TON = 0;  // turn off T4, time measurement stops
    unsigned int measured_time_left; 
    if(time_overflow_left == 1)     // time overflow happens
    {
        measured_time_left = TMR4_period;
        time_overflow_left = 0;
    }
    else                            // the signal sent has returned
    {
        measured_time_left = TMR4;
    }
    TMR4 = 0;
    // operation /2 is used because the ultrasonic pulse travels to the obstacle and back
    // operation *INSTRUCTION_CLOCK_PERIOD is used to get the time in microseconds
    measured_distance_left = (measured_time_left*INSTRUCTION_CLOCK_PERIOD)/2*SPEED_OF_SOUND;        
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
    DelayUs(3); //  3 instead of 10 to make logical one lasts for 10us
    TRIG_RIGHT = 0;
    DelayUs(3);
    while(!ECHO_RIGHT);//  the value of the echo pin becomes 1 (the rising edge detected)
    TMR5 = 0; // reset T5
    IFS1bits.T5IF = 0;
    T5CONbits.TON = 1; // turn on T5, time measurement begins 
    while(ECHO_RIGHT);        // the value of the echo pin becomes 0 (the falling edge detected)
    T5CONbits.TON = 0;  // turn off T4, time measurement stops
    unsigned int measured_time_right; 
    if(time_overflow_right == 1)     // time overflow happens
    {
        measured_time_right = TMR5_period;
        time_overflow_right = 0;
    }
    else                            // the signal sent has returned
    {
        measured_time_right = TMR5;
    }
    TMR5 = 0;
    // operation /2 is used because the ultrasonic pulse travels to the obstacle and back
    // operation *INSTRUCTION_CLOCK_PERIOD is used to get the time in microseconds
    measured_distance_right = (measured_time_right*INSTRUCTION_CLOCK_PERIOD)/2*SPEED_OF_SOUND;        
}

/* 
 * @brief - Function for increasing/decreasing duty cycle for motors
 * @param None
 * @return None
 */
static void ChangeDutyCycle()
{
    if(tempRX1_debug == '+')
    {
        if(duty_cycle_entered1 <= 95)
        {
            duty_cycle_entered1 += 5;
            DutyCyclePWM1(duty_cycle_entered1);
        }
        if(duty_cycle_entered2 <= 95)
        {
            duty_cycle_entered2 += 5;
            DutyCyclePWM2(duty_cycle_entered2);
        }
        tempRX1_debug = 0;
        WriteStringUART1("The duty cycle was increased.");
    }

    else if(tempRX1_debug == '-')
    {
        if(duty_cycle_entered1  >= 5)
        {
            duty_cycle_entered1 -= 5;
            DutyCyclePWM1(duty_cycle_entered1);
        }
        if(duty_cycle_entered2 >= 5)
        {
            duty_cycle_entered2 -= 5;
            DutyCyclePWM2(duty_cycle_entered2);
        }
        tempRX1_debug = 0;
        WriteStringUART1("The duty cycle was decreased.");
    } 
}