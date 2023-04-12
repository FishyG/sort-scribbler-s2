/* 
 * @file    motor.c
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   
 * @version 1.0 : Version initiale
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <catalina_cog.h>
#include "motor.h"

int speed0 = 0;
int dir0 = 0;

int speed1 = 0;
int dir1 = 0;


int wb_motor_set_position(short wheel, int idk)
{
    printf("wb_motor_set_position V2 wheel: %d, idk: %d\n",wheel,idk);
    return 0;
}

int wb_motor_set_velocity(short wheel, int speed)
{
    if (wheel == 0)
    {
        dir0 = (speed < 0) ? 0 : 1;
        speed0 = abs(speed) * 20;
    }
    else if (wheel == 1)
    {
        dir1 = (speed < 0) ? 0 : 1;
        speed1 = abs(speed) * 20;
    }
    
    return 0;
}

// Function controlling motor 0 (left motor)
void fct_pwm0(void)
{
    int i = 0;
    int speed0temp = 0;
    // P27 en sortie et à l'état bas
    _dira(DIR_MOTOR_0, DIR_MOTOR_0);
    _dira(PWM_MOTOR_0, PWM_MOTOR_0);

    while(1)
    {
        if(speed0)
        {
            speed0temp = speed0;

            // Set the direction in accordance to dir0
            _outa(DIR_MOTOR_0, dir0 ? DIR_MOTOR_0 : 0);

            _outa(PWM_MOTOR_0, PWM_MOTOR_0); // PWM high
            while(i < speed0temp)
            {
                i++;
            }
            _outa(PWM_MOTOR_0, 0); // PWM low
            while(i < 100)
            {
                i++;
            }
            i = 0;
        }
    }
}

// Function controlling motor 1 (right motor)
void fct_pwm1(void)
{
    int i = 0;
    int speed1temp = 0;
    // P27 en sortie et à l'état bas
    _dira(DIR_MOTOR_1, DIR_MOTOR_1);
    _dira(PWM_MOTOR_1, PWM_MOTOR_1);

    while(1)
    {
        if(speed1)
        {
            speed1temp = speed1;
            // Set the direction in accordance to dir1
            _outa(DIR_MOTOR_1, dir1 ? DIR_MOTOR_1 : 0);

            _outa(PWM_MOTOR_1, PWM_MOTOR_1); // PWM high
            while(i < speed1temp)
            {
                i++;
            }
            _outa(PWM_MOTOR_1, 0); // PWM low
            while(i < 100)
            {
                i++;
            }
            i = 0;
        }
    }
}

// Function controlling all the motors
void fct_pwm_all(void)
{
    int i = 0;
    int speed1temp = 0;
    int speed0temp = 0;

    _dira(DIR_MOTOR_1, DIR_MOTOR_1);
    _dira(PWM_MOTOR_1, PWM_MOTOR_1);
    _dira(DIR_MOTOR_0, DIR_MOTOR_0);
    _dira(PWM_MOTOR_0, PWM_MOTOR_0);

    while(1)
    {
        speed0temp = speed0;
        speed1temp = speed1;
        // Set the direction of each motot in accordance to their direction
        _outa(DIR_MOTOR_0, dir0 ? DIR_MOTOR_0 : 0);
        _outa(DIR_MOTOR_1, dir1 ? DIR_MOTOR_1 : 0);

        while(i < 100)
        {
            _outa(PWM_MOTOR_0, (speed0temp > i) ? PWM_MOTOR_0 : 0);
            _outa(PWM_MOTOR_1, (speed1temp > i) ? PWM_MOTOR_1 : 0);
            i++;
        }
        i = 0;
    }
}
