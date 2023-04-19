/** 
 * @file    light_sensor.c
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   Fichier .c contenant toutes les fonctions en lien avec les capteurs de
 *          lumière. La fonction wb_light_sensor_enable ne sert à rien. Le cog avec le
 *          convertisseur analogique -> digitale doit être démarrer sur un cog avant de
 *          pouvoir utiliser les fonctions ici présentes. Les fonctions essaient de
 *          recréer le plus fidèlement possible les fonctions de webot.
 * @version 1.0 : Version initiale
 */

#include "robot.h"
#include "light_sensor.h"

extern long sigma;

/**
    @brief Fonction pour lire les capteurs de lumières
    @param sensor Identifiant du capteur.
    @return La valeur de la conversion Analogique-Numérique
*/
int wb_light_sensor_get_value(int sensor)
{
    // For the left light sensor
    if(sensor == 0)
    {
        // Select Light_Left_Ang on the Mux
        _outa(0xf << 22, 0);    // Set the lower 4 bits of the address to 0 (All the Mux channel to 0)
        _outa(MUX_SELECT, MUX_SELECT);  // select the Mux
        _outa(MUX_CHANNEL0, MUX_CHANNEL0);  // set the channel 0 on the Mux
        _outa(MUX_CHANNEL2, MUX_CHANNEL2);  // set the channel 2 on the Mux
    }
    // For the right light sensor
    else if(sensor == 1)
    {
        // Select Light_Right_Ang on the Mux
        _outa(0xf << 22, 0);    // Set the lower 4 bits of the address to 0 (All the Mux channel to 0)
        _outa(MUX_SELECT, MUX_SELECT);  // select the Mux
        _outa(MUX_CHANNEL0, MUX_CHANNEL0);  // set the channel 0 on the Mux
    }
    // For the center light sensor
    else if(sensor == 2)
    {
        // Select Light_Center_Ang on the Mux
        _outa(0xf << 22, 0);    // Set the lower 4 bits of the address to 0 (All the Mux channel to 0)
        _outa(MUX_SELECT, MUX_SELECT);  // select the Mux
        _outa(MUX_CHANNEL1, MUX_CHANNEL1);  // set the channel 1 on the Mux
    }
    else
    {
        printf("INVALID SENSOR INPUT (%d) : wb_light_sensor_get_value",sensor);
    }

    _waitcnt(_clockfreq()/20 +_cnt()); // Wait 50 ms for the analog conversion to happen
    
    return sigma; // return the value of the ADC
}

/**
    @brief Fonction normalement utiliser pour activer les capteurs de lumières (non implémentée).
    @param device Identifiant du capteur.
    @param timeStep Vitesse de la simulation
    @return 0 si tout s'est bien passé.
*/
int wb_light_sensor_enable(int device, int timeStep)
{
    return 0; // return 0 to indicate that the function has finished executing
}
