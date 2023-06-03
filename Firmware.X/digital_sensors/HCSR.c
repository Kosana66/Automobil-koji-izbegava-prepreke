/* 
 * File:   HCSR.c
 * Author: kosana
 *
 * Created on 29.05.2023., 22.39
 */

/// Header file for HC-SR04 sensors
#include "HCSR.h"

/* 
 * @brief - Function for configuring pins for HC - SR04 sensors
 * @param None
 * @return None
 */
void ConfigureHCSR04Pins(void)
{
    TRISDbits.TRISD2 = 0;   // output trigger pin for left position sensor
    TRISDbits.TRISD9 = 0;   // output trigger pin for right position sensor
    TRISDbits.TRISD8 = 1;   // input echo pin for left position sensor
    TRISAbits.TRISA11 = 1;  // input echo pin for right position sensor

    TRIG_LEFT = 0;  
    TRIG_RIGHT = 0;    
}
