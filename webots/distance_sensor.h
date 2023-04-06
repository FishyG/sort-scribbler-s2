/* 
 * @file    distance_sensor.h
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   .h de distance_sensor.c
 * @version 1.0 : Version initiale
 */

#ifndef DISTANCE_SENSOR_H
#define	DISTANCE_SENSOR_H

#define OBS_TX_LEFT 6
#define OBS_TX_RIGHT 15
#define OBS_RX 1 << 20

//prototype
int wb_distance_sensor_get_value(int sensor);

int wb_distance_sensor_enable(int sensor, int time_step);

#endif	/* DISTANCE_SENSOR_H */
