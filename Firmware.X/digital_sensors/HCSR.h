/* 
 * File:   HCSR.h
 * Author: kosana
 *
 * Created on 29.05.2023., 22.35
 */

#ifndef HCSR_H
#define	HCSR_H

///library for MCU
#include <p30fxxxx.h>

// macros for echo and trig pins
#define TRIG_LEFT LATDbits.LATD2
#define ECHO_LEFT PORTDbits.RD8
#define TRIG_RIGHT LATDbits.LATD3
#define ECHO_RIGHT PORTDbits.RD9

/// Function for configuring pins for HC - SR04 sensors
void ConfigureHCSR04Pins(void);

#endif	/* HCSR_H */