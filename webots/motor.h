/** 
 * @file    motor.h
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   .h de motor.c (voir motor.c pour le brief)
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

/**
    @brief Fonction pour définir la position des moteurs (non implémentée).
    @param wheel Identifiant de la roue.
    @param pos Valeur de la position.
    @return 0 si tout s'est bien passé.
*/
int wb_motor_set_position(short wheel, int pos);

/**
    @brief Fonction pour définir la vélocité des moteurs.
    @param wheel Identifiant de la roue.
    @param speed Vitesse de la roue.
    @return 0 si tout s'est bien passé.
*/
int wb_motor_set_velocity(short wheel, int speed);

/**
    @brief Fonction pour controller le pwm des moteurs.
*/
void fct_pwm_all(void);

#endif	/* MOTOR_H */
