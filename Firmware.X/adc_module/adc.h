/* 
 * File:   adc.h
 * Author: kosana
 *
 * Created on 03.05.2023., 19.55
 */

#ifndef ADC_H
#define	ADC_H

///library for MCU
#include <p30fxxxx.h>

/// Function for configuring ADC pins
void ConfigureADCPins(void);

/// Function for initialization AD conversion
void InitADC(void);

#endif	/* ADC_H */