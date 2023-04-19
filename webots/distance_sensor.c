/* 
 * @file    distance_sensor.c
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   Fichier .c contenant toutes les fonctions en lien avec les capteurs de
 *          distance. La fonction wb_distance_sensor_enable ne sert à rien. Les fonctions
 *          essaient de recréer le plus fidèlement possible les fonctions de webot.
 * @version 1.0 : Version initiale
 */

// Includes
#include "distance_sensor.h"
#include "synth.h"
#include "stdio.h"
#include "robot.h"
#include "catalina_cog.h"
#include "propeller.h"

extern long sigma;  // Variable pour le résultat de l'ADC

/**
    @brief Fonction pour lire les capteurs de distances.
    @param sensor Identifiant du capteur.
    @return La valeur de la conversion Analogique-Numérique.
*/
int wb_distance_sensor_get_value(int sensor)
{
    int return_value = 0;   // For the return value
    char pin = 0;   // Pin for the ir LEDs
    
    // For the distance sensor in front of the scribbler
    if (sensor < 2)
    {
        _dira(1 << OBS_TX_LEFT, 1 << OBS_TX_LEFT);  // Set the port as an output
        _dira(1 << OBS_TX_RIGHT, 1 << OBS_TX_LEFT); // Set the port as an output
        _dira(1 << OBS_RX, 0);  // Set the port as an input
        
        if(sensor == 0) // For the left sensor
            pin = 6;
        else if (sensor == 1)   // For the right sensor
            pin = 15;
        
        synth('A',pin, 38000);  // Start the generator
        _waitcnt(_clockfreq()/100 +_cnt()); // Delay 10 ms
        return_value = _ina() & OBS_RX;   // Read Obs_Rx (P20)
        silence_a(pin);     // Stop the generator
        _waitcnt(_clockfreq()/50 +_cnt()); // Delay 20 ms (to not overload the IR LEDs)
    }
    else if (sensor >= 2)
    {
        // For the left floor sensor
        if(sensor == 2)
        {
            // Select Line_Left_Ang on the Mux
            _outa(0xf << 22, 0);
            _outa(MUX_SELECT, MUX_SELECT);
            _outa(MUX_CHANNEL2, MUX_CHANNEL2);
            _outa(MUX_CHANNEL0, MUX_CHANNEL0);
            _outa(MUX_CHANNEL1, MUX_CHANNEL1);
        }
        // For the right floor sensor
        else if(sensor == 3)
        {
            // Select Line_Right_Ang on the Mux
            _outa(0xf << 22, 0);
            _outa(MUX_SELECT, MUX_SELECT);
            _outa(MUX_CHANNEL2, MUX_CHANNEL2);
            _outa(MUX_CHANNEL1, MUX_CHANNEL1);
        }
        // Read the current of the motors
        else if(sensor == 69)
        {
            // Select Mot_I_Ang on the Mux
            _outa(0xf << 22, 0);
            // _outa(MUX_SELECT, 0);
            // _outa(MUX_CHANNEL2, MUX_CHANNEL2);
            // _outa(MUX_CHANNEL1, MUX_CHANNEL1);
        }
        _waitcnt(_clockfreq()/50 +_cnt()); // Wait 20 ms for the analog conversion to happen
        return_value = sigma;
    }
    else
    {
        printf("INVALID Sensor : %d check distance_sensor.c\n",sensor);
    }
    
    return return_value;
}

/**
    @brief Fonction normalement utiliser pour activer les capteurs de distance (non implémentée).
    @param sensor Identifiant du capteur.
    @param time_step Vitesse de la simulation
    @return 0 si tout s'est bien passé.
*/
int wb_distance_sensor_enable(int sensor, int time_step)
{
    return 0;   // return 0 to indicate that the function has finished executing
}
