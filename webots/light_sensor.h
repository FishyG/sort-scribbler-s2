/* 
 * @file    light_sensor.h
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   .h de light_sensor.c
 * @version 1.0 : Version initiale
 */

#ifndef LIGHT_SENSOR_H
#define	LIGHT_SENSOR_H

//prototype
int wb_light_sensor_get_value(int sensor);

int wb_light_sensor_enable(int device, int timeStep);

#endif	/* LIGHT_SENSOR_H */
