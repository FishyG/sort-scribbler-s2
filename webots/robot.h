/* 
 * @file    robot.h
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   .h de robot.c (voir robot.c pour le brief)
 * @version 1.0 : Version initiale
 */

#ifndef ROBOT_H
#define	ROBOT_H

//prototype

// For ADC
#define labyrinthe_CLOCKFREQ  80000000
#define labyrinthe_CLOCKMODE  0x6F
#define labyrinthe_ARRAYTYPE 0 // array contains PASM program
#define labyrinthe_PROG_SIZE 188    // bytes

// Define the I/O of the Mux
#define MUX_CHANNELS 1 << 22
#define MUX_CHANNEL0 1 << 22
#define MUX_CHANNEL1 1 << 23
#define MUX_CHANNEL2 1 << 24
#define MUX_SELECT 1 << 25

// Replace "WbDeviceTag" by a short
typedef unsigned short WbDeviceTag;

/**
    @brief Fonction permettant d'initialiser les différents modules du robot. Démarre
           les différents cogs (pwm_motor, pwm_led, labyrinthe_arrayvet step_counter) 
    @return 0 si tout s'est bien passé.
*/
int wb_robot_init(void);

/**
    @brief Ne sert à rien. Est normalement utilisé pour "cleanup" l'environnement virtuel.
*/
void wb_robot_cleanup(void);


int wb_robot_get_device(const char* device);

/**
    @brief Fonction pour remplacer wb_robot_step. Attend le delais fournis en paramètre.
           Cette fonction recrée plus ou moins celle de webot. 
    @param duration Temps d'attente pour le timestep.
    @return duration (le même param que donné en entrer)
*/
int wb_robot_step(int duration);

/**
    @brief Fonction pour compter le temps du timeset_counter. Attend que timeset_launch soit True (1).
           La variable globale timeset_ready devient True (1) lorsque le délais est terminé.
*/
void step_counter(void);

#endif	/* ROBOT_H */
