/**
 * @file    motor.c
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   Fichier .c contenant toutes les fonctions en lien avec le controle des
 *          moteurs. La fonction wb_motor_set_position ne sert à rien. La fonction
 *          fct_pwm_all doit être démarrer sur un cog. Les fonctions essaient de
 *          recréer le plus fidèlement possible les fonctions de webot.
 * @version 1.0 : Version initiale
 */ 

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <catalina_cog.h>
#include "motor.h"

// Global variables
int speed0 = 0; // For the speed of the left motor
int dir0 = 0;   // For the direction of the left motor

int speed1 = 0; // For the speed of the right motor
int dir1 = 0;   // For the direction of the right motor 

/**
    @brief Fonction pour définir la position des moteurs (non implémentée, car je n'ai pas besoin).
    @param wheel Identifiant de la roue.
    @param pos Valeur de la position.
    @return 0 si tout s'est bien passé.
*/
int wb_motor_set_position(short wheel, int pos)
{
    printf("wb_motor_set_position V2 wheel: %d, pos: %d\n",wheel,pos);
    return 0; // return 0 to indicate that the function has finished executing
}

/**
    @brief Fonction pour définir la vélocité des moteurs.
    @param wheel Identifiant de la roue.
    @param speed Vitesse de la roue.
    @return 0 si tout s'est bien passé.
*/
int wb_motor_set_velocity(short wheel, int speed)
{
    if (wheel == 0)
    {
        dir0 = (speed < 0) ? 0 : 1; // Set the direction of the motor based on the speed
        speed0 = abs(speed) * 20;   // Convert the speed to asbsolute
    }
    else if (wheel == 1)
    {
        dir1 = (speed < 0) ? 0 : 1; // Set the direction of the motor based on the speed
        speed1 = abs(speed) * 20;   // Convert the speed to asbsolute
    }
    
    return 0; // return 0 to indicate that the function has finished executing
}

/**
    @brief Fonction pour controller le pwm des moteurs.
*/
void fct_pwm_all(void)
{
    int i = 0;  // For the counter
    int speed1temp = 0; // For the temporary speed of motor 1
    int speed0temp = 0; // For the temporary speed of motor 0

    // Set the direction to output for the direction and the pwm pin of each motor
    _dira(DIR_MOTOR_1, DIR_MOTOR_1);    // Set direction for motor 1
    _dira(PWM_MOTOR_1, PWM_MOTOR_1);    // Set PWM for motor 1
    _dira(DIR_MOTOR_0, DIR_MOTOR_0);    // Set direction for motor 0
    _dira(PWM_MOTOR_0, PWM_MOTOR_0);    // Set PWM for motor 0

    while(1)
    {
        speed0temp = speed0; // Store the speed0 in speed0tempso it does not change during the PWM
        speed1temp = speed1; // Store the speed1 in speed1temp so it does not change during the PWM
        // Set the direction of each motot in accordance to their direction
        _outa(DIR_MOTOR_0, dir0 ? DIR_MOTOR_0 : 0); // If dir0 is true, set the motor 0 direction to DIR_MOTOR_0, else set it to 0
        _outa(DIR_MOTOR_1, dir1 ? DIR_MOTOR_1 : 0); // If dir1 is true, set the motor 1 direction to DIR_MOTOR_1, else set it to 0

        // Loop to control the PWM for both motors
        while(i < 100)
        {
            // If the current speed for each motor is greater than the loop 
            // index i, set the PWM output to the respective motor, else set it to 0
            _outa(PWM_MOTOR_0, (speed0temp > i) ? PWM_MOTOR_0 : 0);
            _outa(PWM_MOTOR_1, (speed1temp > i) ? PWM_MOTOR_1 : 0);
            i++;
        }
        i = 0;  // Reset the loop index i to 0 for the next iteration
    }
}
