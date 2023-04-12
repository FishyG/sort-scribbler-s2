/* 
 * @file    light_sensor.c
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   
 * @version 1.0 : Version initiale
 */

#include "robot.h"
#include "light_sensor.h"

extern long sigma;

int wb_light_sensor_get_value(int sensor)
{
    printf("fdfd%d\n",sensor);
    if(sensor == 0)
    {
        // Select Light_Left_Ang on the Mux
        _outa(0xf << 22, 0);
        _outa(MUX_SELECT, MUX_SELECT);
        _outa(MUX_CHANNEL0, MUX_CHANNEL0);
        _outa(MUX_CHANNEL2, MUX_CHANNEL2);
    }
    else if(sensor == 1)
    {
        // Select Light_Right_Ang on the Mux
        _outa(0xf << 22, 0);
        _outa(MUX_SELECT, MUX_SELECT);
        _outa(MUX_CHANNEL0, MUX_CHANNEL0);
    }
    else if(sensor == 2)
    {
        // Select Light_Center_Ang on the Mux
        _outa(0xf << 22, 0);
        _outa(MUX_SELECT, MUX_SELECT);
        _outa(MUX_CHANNEL1, MUX_CHANNEL1);
    }
    else
    {
        printf("INVALID SENSOR INPUT (%d) : wb_light_sensor_get_value",sensor);
    }

    _waitcnt(_clockfreq()/20 +_cnt()); // Wait 50 ms for the analog conversion to happen
    
    return sigma;
}

int wb_light_sensor_enable(int device, int timeStep)
{
    return 0;
}
