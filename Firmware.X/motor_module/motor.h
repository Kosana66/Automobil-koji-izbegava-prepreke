/* 
 * File:   motor.h
 * Author: kosana
 *
 * Created on 30.05.2023., 16.03
 */

#ifndef MOTOR_H
#define	MOTOR_H

///library for MCU
#include <p30fxxxx.h>
/*
FRONT MOTOR
 forward           backward
IN1 =               IN1 =
IN2 =               IN2 =

BACK MOTOR
 forward         backward
IN3 =               IN3 =
IN4 =               IN4 =
 
*/

#define IN1         LATBbits.LATB10 
#define IN2         LATBbits.LATB11
#define IN3         LATFbits.LATF0 
#define IN4         LATFbits.LATF1 



/// Function for configuring pins for motors
void ConfigureMotorsPins();

/// Function for stopping the motors
void StopMotors();

/// Function for driving a car forward
void DriveForward();

/// Function for driving a car backward
void DriveBackward();

/// Function for turning a car left
void TurnLeft();

/// Function for turning a car left
void TurnRight();


#endif	/* MOTOR_H */

