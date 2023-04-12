/* 
 * @file    distance_sensor.c
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   
 * @version 1.0 : Version initiale
 */


#include "distance_sensor.h"
#include "synth.h"
#include "stdio.h"
#include "robot.h"
#include "catalina_cog.h"
#include "propeller.h"

extern long sigma;

int wb_distance_sensor_get_value(int sensor)
{
    int return_value = 0;
    char pin = 0;
    
    if (sensor < 2)
    {
        _dira(1 << OBS_TX_LEFT, 1 << OBS_TX_LEFT);  // Set the port as an output
        _dira(1 << OBS_TX_RIGHT, 1 << OBS_TX_LEFT); // Set the port as an output
        _dira(1 << OBS_RX, 0);  // Set the port as an input
        
        if(sensor == 0)
            pin = 6;
        else if (sensor == 1)
            pin = 15;
        
        
        synth('A',pin, 38000);  // Start the generator
        _waitcnt(_clockfreq()/100 +_cnt()); // Delay 10 ms
        return_value = _ina() & OBS_RX;   // Read Obs_Rx (P20)
        silence_a(pin);     // Stop the generator
        _waitcnt(_clockfreq()/50 +_cnt()); // Delay 20 ms (to not overload the IR LEDs)
    }
    else if (sensor >= 2)
    {
        // Run the ir led
        _dira(1 << 12, 1 << 12);
        _outa(1 << 12, 0);

        if(sensor == 2)
        {
            // Select Line_Left_Ang on the Mux
            _outa(0xf << 22, 0);
            _outa(MUX_SELECT, MUX_SELECT);
            _outa(MUX_CHANNEL2, MUX_CHANNEL2);
        }
        else if(sensor == 3)
        {
            // Select Line_Right_Ang on the Mux
            _outa(0xf << 22, 0);
            _outa(MUX_SELECT, MUX_SELECT);
            _outa(MUX_CHANNEL0, MUX_CHANNEL0);
            _outa(MUX_CHANNEL1, MUX_CHANNEL1);
        }
        _waitcnt(_clockfreq()/20 +_cnt()); // Wait 50 ms for the analog conversion to happen
        return_value = sigma;
    }
    else
    {
        printf("INVALID Sensor : %d check distance_sensor.c\n",sensor);
    }
    
    return return_value;
}

int wb_distance_sensor_enable(int sensor, int time_step)
{
    return 0;
}
