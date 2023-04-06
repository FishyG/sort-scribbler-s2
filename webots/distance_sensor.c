/* 
 * @file    distance_sensor.c
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   
 * @version 1.0 : Version initiale
 */


#include "distance_sensor.h"
#include "synth.h"
#include "catalina_cog.h"
#include "propeller.h"

int wb_distance_sensor_get_value(int sensor)
{
    int retour = 0;
    
    _dira(1 << OBS_TX_LEFT, 1 << OBS_TX_LEFT);
    _dira(1 << OBS_TX_RIGHT, 1 << OBS_TX_LEFT);
    _dira(1 << OBS_RX, 0);
    //_outa(0xf << 22, );

    synth('A',15, 38000);
    _waitcnt(_clockfreq()/10 +_cnt()); // Delay 100 ms
    retour = _ina() & OBS_RX;
    silence_a(15);
    _waitcnt(_clockfreq()/10 +_cnt()); // Delay 100 ms
    return retour;
}

int wb_distance_sensor_enable(int sensor, int time_step)
{
    return 0;
}
