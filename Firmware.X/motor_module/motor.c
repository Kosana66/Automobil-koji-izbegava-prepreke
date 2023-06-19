/* 
 * File:   motor.c
 * Author: kosana
 *
 * Created on 30.05.2023., 16.11
 */

/// Header file for controlling the motors
#include "motor.h"

/* 
 * @brief - Function for configuring pins for motors
 * @param None
 * @return None
 */
void ConfigureMotorsPins()
{
    TRISBbits.TRISB10 = 0; // output pin IN1
    TRISBbits.TRISB11 = 0; // output pin IN2
    TRISFbits.TRISF0 = 0; // output pin IN3
    TRISFbits.TRISF1 = 0; // output pin IN4
    
    ADPCFGbits.PCFG11 = 1; // digital pin IN1
    ADPCFGbits.PCFG12 = 1; // digital pin IN2
}

/* 
 * @brief - Function for stopping the motors
 * @param None
 * @return None
 */
void StopMotors()
{
    //in1 , in2 for right motor
    IN1=0;
    IN2=0;
    //in3 , in4 for left motor
    IN3=0;
    IN4=0;
}

/* 
 * @brief - Function for driving a car forward
 * @param None
 * @return None
 */
void DriveForward()
{
    IN1=1;
    IN2=0;
    IN3=0;
    IN4=1; 
}

/* 
 * @brief - Function for driving a car backward
 * @param None
 * @return None
 */
void DriveBackward()
{
    IN1=0;
    IN2=1;
    IN3=1;
    IN4=0;
}

/* 
 * @brief - Function for turning a car left
 * @param None
 * @return None
 */
void TurnLeft()
{
    IN1=1;
    IN2=0;
    IN3=1;
    IN4=0; 
}

/* 
 * @brief - Function for turning a car right
 * @param None
 * @return None
 */
void TurnRight()
{
    IN1=0;
    IN2=1;
    IN3=0;
    IN4=1; 
}