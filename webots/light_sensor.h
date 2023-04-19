/* 
 * @file    light_sensor.h
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   .h de light_sensor.c (voir light_sensor.c pour le brief)
 * @version 1.0 : Version initiale
 */

#ifndef LIGHT_SENSOR_H
#define	LIGHT_SENSOR_H

//prototype
/**
    @brief Fonction pour lire les capt
    @param sensor Identifiant du capteur.
    @return La valeur de la conversion Analogique-Numérique
*/
int wb_light_sensor_get_value(int sensor);

/**
    @brief Fonction normalement utiliser pour activer les capteurs de lumières (non implémentée).
    @param device Identifiant du capteur.
    @param timeStep Vitesse de la simulation
    @return 0 si tout s'est bien passé.
*/
int wb_light_sensor_enable(int device, int timeStep);

#endif	/* LIGHT_SENSOR_H */
