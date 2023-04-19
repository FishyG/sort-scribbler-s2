/* 
 * @file    distance_sensor.h
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   .h de distance_sensor.c (voir distance_sensor.c pour le brief)
 * @version 1.0 : Version initiale
 */

#ifndef DISTANCE_SENSOR_H
#define	DISTANCE_SENSOR_H

#define OBS_TX_LEFT 6
#define OBS_TX_RIGHT 15
#define OBS_RX 1 << 20

//prototype

/**
    @brief Fonction pour lire les capteurs de distances.
    @param sensor Identifiant du capteur.
    @return La valeur de la conversion Analogique-Numérique.
*/
int wb_distance_sensor_get_value(int sensor);

/**
    @brief Fonction normalement utiliser pour activer les capteurs de distance (non implémentée).
    @param sensor Identifiant du capteur.
    @param time_step Vitesse de la simulation
    @return 0 si tout s'est bien passé.
*/
int wb_distance_sensor_enable(int sensor, int time_step);

#endif	/* DISTANCE_SENSOR_H */
