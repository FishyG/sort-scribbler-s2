/* 
 * @file    motor.h
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   .h de motor.c
 * @version 1.0 : Version initiale
 */

#ifndef MOTOR_H
#define	MOTOR_H

#define PWM_MOTOR_0 1<<18
#define DIR_MOTOR_0 1<<16

#define PWM_MOTOR_1 1<<19
#define DIR_MOTOR_1 1<<17

#define INFINITY 420

//prototype
int wb_motor_set_position(short wheel, int idk);

int wb_motor_set_velocity(short wheel, int speed);

void fct_pwm0(void);
void fct_pwm1(void);
void fct_pwm_all(void);

#endif	/* MOTOR_H */
