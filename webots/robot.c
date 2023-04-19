/* 
 * @file    robot.c
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   Fichier .c contenant toutes les fonctions en lien avec le controle
 *          général du robot. Ce code imite (en partie) les fonctions de webot.
 * @version 1.0 : Version initiale
 */

// Includes
#include <catalina_cog.h>
#include <stdio.h> 
#include <string.h>
#include "led.h"
#include "robot.h"
#include "motor.h"


// Global variables
long sigma = 0;     // Variable for the analog to digital conversion
char timeset_ready = 0; // Variable when the timestep is done
char timeset_launch = 0;    // Variable use to launch the timer
char timeset_counter = 0;   // How long the timer will wait

// For the ADC
unsigned long labyrinthe_array[] =
{
    0xa0fff401, 0x58fff048, 0x54fff01a, 0x50fff01b, 
    0xa0bfec2b, 0xa0bc5df0, 0x68bfec2c, 0xa0bc5e29, 
    0xa0bc6029, 0x28fc6001, 0x64bfe82c, 0x5cfc421e, 
    0x5cfc5022, 0xa0bc6631, 0x68bfe82c, 0x5cfc421e, 
    0x5cfc5022, 0x84bc6233, 0x873c622a, 0x5c680017, 
    0x94bc5e30, 0x2afc6001, 0x5c54000a, 0x64bfec2c, 
    0x5cfc5022, 0x84bc6233, 0x44bc622a, 0x40fc6200, 
    0x083c622e, 0x5c7c0018, 0xa0bc65f1, 0x80bc642d, 
    0xf8fc6400, 0x5c7c0000, 0xa0bc65f1, 0x80fc6410, 
    0xf8bc642f, 0xa4bc63fc, 0xf8fc6400, 0x80bc63fc, 
    0x5c7c0000, 0x00000200, 0x000000ff, 0x04000000, 
    0x00000002, 0x00009c40, 0x00000000
};

/**
    @brief Fonction pour définir les "ids" des différents composants du robot scribbler.
    @param device Nom (tableau de char) de la "device".
    @return Id de la "device".
*/
int wb_robot_get_device(const char* device)
{
    int return_value = 0;

    // Mega if to check the name of the device
    // Left light sensor
    if (strcmp(device,"ls_left") == 0)
    {
        return_value = 0;
    }
    // Right light sensor
    else if (strcmp(device,"ls_right") == 0)
    {
        return_value = 1;
    }
    // Center light sensor
    else if (strcmp(device,"ls_center") == 0)
    {
        return_value = 2;
    }
    // Left LED
    else if (strcmp(device,"led_0") == 0)
    {
        return_value = 0;
    }
    // Middle left LED 
    else if (strcmp(device,"led_1") == 0)
    {
        return_value = 1;
    }
    // Middle right LED
    else if (strcmp(device,"led_2") == 0)
    {
        return_value = 2;
    }
    // Right LED
    else if (strcmp(device,"led_3") == 0)
    {
        return_value = 3;
    }
    // Left wheel
    else if (strcmp(device,"wheel1") == 0)
    {
        return_value = 0;
    }
    // Right wheel
    else if (strcmp(device,"wheel2") == 0)
    {
        return_value = 1;
    }
    // Left distance sensor
    else if (strcmp(device,"ds_left") == 0)
    {
        return_value = 0;
    }
    // Right distance sensor
    else if (strcmp(device,"ds_right") == 0)
    {
        return_value = 1;
    }
    // Left floor sensor
    else if (strcmp(device,"fs_left") == 0)
    {
        return_value = 2;
    }
    // Right floor sensor
    else if (strcmp(device,"fs_right") == 0)
    {
        return_value = 3;
    }

    return return_value;
}

/**
    @brief Fonction permettant d'initialiser les différents modules du robot. Démarre
           les différents cogs (pwm_motor, pwm_led, labyrinthe_arrayvet step_counter) 
    @return 0 si tout s'est bien passé.
*/
int wb_robot_init()
{
    unsigned long stack_pwm_motor[150];     // Stack for the cog that will run fct_pwm_all
    unsigned long stack_pwm_led[150];       // Stack for the cog that will run del_shift_pwm
    unsigned long stack_step_counter[150];  // Stack for the cog that will run step_counter

    printf("Starting up... \n");
    printf("ADC started on cog %d\n",_coginit((long)&sigma >> 2, (int)labyrinthe_array >> 2, ANY_COG)); // Start the ADC on a cog
    _dira(0xf << 22, 0xf << 22);    // Set the control for the MUX as output
    
    // Set MUX of the adc to gnd (improve the range of the adc)
    _outa(0xf << 22, 0);
    _outa(MUX_CHANNEL2, MUX_CHANNEL2);  

    printf("Motor PWM started on cog %d\n",_coginit_C(&fct_pwm_all, &stack_pwm_motor[150])); // Start the pwm 0 on a cog
    printf("LED PWM started on cog %d\n",_coginit_C(&del_shift_pwm, &stack_pwm_led[150])); // Start the pwm 0 on a cog
    printf("Step_counter started on cog %d\n",_coginit_C(&step_counter, &stack_step_counter[150])); // Start the step_counter on a cog

    play("Mario", 200, 21); // Play music instead of just waiting for the adc (cooler :) )
    //_waitcnt(_clockfreq()/10 +_cnt()); // Delay 100 ms for the adc
    
    printf("Exiting robot init\n");
    return 0; // return 0 to indicate that the function has finished executing
}

/**
    @brief Ne fait rien. Est normalement utilisé pour "cleanup" l'environnement virtuel.
*/
void wb_robot_cleanup(void)
{
    // Do nothing :)
}

/**
    @brief Fonction pour remplacer wb_robot_step. Attend le delais fournis en paramètre.
           Cette fonction recrée plus ou moins celle de webot. 
    @param duration Temps d'attente pour le timestep.
    @return duration (le même param que donné en entrer)
*/
int wb_robot_step(int duration)
{
    timeset_counter = duration; // Set the duration to the one in param
    timeset_launch = 1; // Launche a timer
    // Wait until the timer is done
    while (!timeset_ready)
    {
        printf("Waiting... \n"); // Waiting...
    }
    timeset_ready = 0; // Reset the timer
    timeset_launch = 1; // Start the counter for the next time_step

    return duration;    // return the duration
}

/**
    @brief Fonction pour compter le temps du timeset_counter. Attend que timeset_launch soit True (1).
           La variable globale timeset_ready devient True (1) lorsque le délais est terminé.
*/
void step_counter(void)
{
    while (1)
    {
        // Wait for timeset_launch before start the timer
        if(timeset_launch)
        {
            timeset_ready = 0;  // Set ready back to 0 in case I forget
            _waitcnt(_clockfreq() / 1000 * timeset_counter + _cnt()); // Wait the timeset_counter
            timeset_ready = 1;  // Ready when the delay above is done
            timeset_launch = 0; // Set launch back to 0 to stop
        }
    }
}
