/* 
 * File:   uart.h
 * Author: kosana
 *
 * Created on 03.05.2023., 21.25
 */

#ifndef UART_H
#define	UART_H

///library for MCU
#include <p30fxxxx.h>

/// Function for initializing UART1 
void InitUART1(void);

/// Function for writing one character over UART1
void WriteCharUART1(unsigned int data);

/// Function for writing string over UART1
void WriteStringUART1(register const char *str);

/// Function for writing a four-digit number over UART1
void WriteUART1dec2string(unsigned int data);

/// Function for initializing UART2 
void InitUART2(void);

/// Function for writing one character over UART2
void WriteCharUART2(unsigned int data);

/// Function for writing string over UART2
void WriteStringUART2(register const char *str);

/// Function for writing a four-digit number over UART2
void WriteUART2dec2string(unsigned int data);

/// Function for writing a distance from obstacle over UART2
void WriteObstacleDistance2(float data);

#endif	/* UART_H */

