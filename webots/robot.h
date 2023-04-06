/* 
 * @file    robot.h
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   .h de robot.c
 * @version 1.0 : Version initiale
 */

#ifndef ROBOT_H
#define	ROBOT_H

//prototype

#define labyrinthe_CLOCKFREQ  80000000
#define labyrinthe_CLOCKMODE  0x6F

#define labyrinthe_ARRAYTYPE 0 // array contains PASM program
#define labyrinthe_PROG_SIZE 188    // bytes

// Définition des I/O de la carte
#define MUX_CHANNELS 1 << 22
#define MUX_CHANNEL0 1 << 22
#define MUX_CHANNEL1 1 << 23
#define MUX_CHANNEL2 1 << 24
#define MUX_SELECT 1 << 25

typedef unsigned short WbDeviceTag;

int wb_robot_init(void);

void wb_robot_cleanup(void);

int wb_robot_step(int duration);

int wb_robot_get_device(const char* device);

void step_counter(void);

#endif	/* ROBOT_H */
