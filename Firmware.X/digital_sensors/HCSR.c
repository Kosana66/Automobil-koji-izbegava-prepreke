/* 
 * File:   HCSR.c
 * Author: kosana
 *
 * Created on 29.05.2023., 22.39
 */

#include <p30fxxxx.h>

/// Header file for HC-SR04 sensors
#include "HCSR.h"

/* 
 * @brief - Function for configuring pins for HC - SR04 sensors
 * @param None
 * @return None
 */
void ConfigureHCSR04Pins(void)
{
    TRISDbits.TRISD2 = 0;   // Trigger for left HC-SR04
    TRISDbits.TRISD9 = 0;   // Trigger for right HC-SR04
    TRISDbits.TRISD8 = 1;   // Echo for left HC-SR04
    TRISAbits.TRISA11 = 1;   // Echo for right HC-SR04

    TRIG_LEFT = 0;  
    TRIG_RIGHT = 0;   
    ECHO_LEFT = 1;   
    ECHO_LEFT = 1;   
}

/// Function for initialization HC - SR04 sensors
void InitHCSR04Sensors(void)
{
    //left position sensor
    IEC0bits.INT0IE = 1; // INT0 interrupt enabled   
    IFS0bits.INT0IF = 0;  // INT0 interrupt flag cleared
    INTCON2bits.INT0EP = 0; // interrupt 0 is sensitive to the rising edge
      
    //right position sensor
    IEC1bits.INT1IE = 1;  // INT1 interrupt enabled   
    IFS1bits.INT1IF = 0; // INT1 interrupt flag cleared
    INTCON2bits.INT1EP = 0; // interrupt 1 is sensitive to the rising edge
}









