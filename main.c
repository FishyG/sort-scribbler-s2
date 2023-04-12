/*
##########################################################################################################
@file     scribbler_s2_collision_avoidance.c
@author   Jessy-Grimard Maheu, 
@date     15 Mars 2023
@version  1.0 : Version initiale
##########################################################################################################
@brief    Programme permettant de contrôler le robot scribbler S2 dans le monde réelle de Webots. Le 
          robot se déplace par lui-même et évite les obstacles tel que les murs ou une falaise. Lorsque
          ces obstacles sont détectés, le robot recule un court instant et poursuit sa course.
##########################################################################################################
       __
     <(o )___
      ( ._> /
       `---'
*/

#include "webots/distance_sensor.h"
#include "webots/light_sensor.h"
#include "webots/motor.h"
#include "webots/robot.h"
#include "webots/led.h"
#include <stdio.h>
#include <stdlib.h>

#define TIME_STEP 32

// char intensite_del[8] = {0,0,0,5,0,0,0,0};
// extern char intensite_del[];
//int wb_motor_set_position(int wheel, int idk);

int main(int argc, char *argv[])
{
    int i = 0;
    int deeznuts = 0;
    int counter = 0;
    int light_index = 0;
    int avoid_obstacle_counter_right = 0;   // Counter for the right turn action
    int avoid_obstacle_counter_left = 0;    // Counter for the left turn action
    int led_brightness = 0;                 // Brightness for the blue LED
    int avg_speed = 0;                   // Average speed
    int left_speed = 1.0;                // Speed of the left motor
    int right_speed = 1.0;               // Speed of the right motor
    int fs_values[2];                    // Array of values of the floor sensors
    int ds_values[2];                    // Array of values of the distance sensors
    int ls_values[3];                    // Array of values of the light sensors
    int ls_max = 0;
    
    
    // For the light sensor
    WbDeviceTag ls[3];
    char ls_names[3][12] = {"ls_left", "ls_right", "ls_center"};
    
    // For the distance sensor
    WbDeviceTag ds[2];
    char ds_names[2][10] = {"ds_left", "ds_right"};
    
    // For the floor sensor
    WbDeviceTag fs[2];
    char fs_names[2][10] = {"fs_left", "fs_right"};
    
    // For the LED
    WbDeviceTag leds[4];
    char led_names[4][10] = {"led_0","led_1","led_2","led_3"};
    
    // For the motors
    WbDeviceTag wheels[2];
    char wheels_names[2][8] = {"wheel1", "wheel2"};

    wb_robot_init();
    
    // ################################################ 
    // ############ Devices initialization ############ 
    // ################################################ 
    // Initialize the light sensors and enable them
    for (i = 0; i < 3; i++) {
        ls[i] = wb_robot_get_device(ls_names[i]);
        wb_light_sensor_enable(ls[i], TIME_STEP);
    }

    // Initialize the wall sensors (ditance sensors) and enable them  
    for (i = 0; i < 2; i++) {
        ds[i] = wb_robot_get_device(ds_names[i]);
        wb_distance_sensor_enable(ds[i], TIME_STEP);
    }
    
    // Initialize the floor sensors (ditance sensors) and enable them
    for (i = 0; i < 2; i++) {
        fs[i] = wb_robot_get_device(fs_names[i]);
        wb_distance_sensor_enable(fs[i], TIME_STEP);
    }
    
    // Initialize the LEDs
    for (i = 0; i < 4; i++) {
        leds[i] = wb_robot_get_device(led_names[i]);
    }
    
    // Initialize all the motors
    for (i = 0; i < 2; i++) {
        wheels[i] = wb_robot_get_device(wheels_names[i]);
// FIX ME PLEASE        Fwb_motor_set_position(wheels[i], INFINITY);
    }

    // ################################################ 
    // ################## Main Loop  ################## 
    // ################################################ 
    /* main loop
    * Perform simulation steps of TIME_STEP milliseconds
    * and leave the loop when the simulation is over
    */
    /*while (1)
    {
        wb_led_set(leds[0], 0x007f00);
        _waitcnt(_clockfreq()*2 +_cnt()); // Delay 10 ms

        // Update the data of the floor sensors
        for (i = 0; i < 3; i++)
        {
            ls_values[i] = wb_light_sensor_get_value(ls[i]);
            printf("Value of %s : %d\n",ls_names[i],fs_values[i]);
        }
    }*/

    while (wb_robot_step(TIME_STEP) != -1) {
        // Reset the speed to it's default
        left_speed = 1.0;
        right_speed = 1.0;

        // If either one of the counter are not yet done it will decrease them by 1
        if (avoid_obstacle_counter_right > 0 || avoid_obstacle_counter_left > 0 || deeznuts) 
        {
            if (avoid_obstacle_counter_right > 0)
            {
                // Put the motors in reverse and turn slightly
                left_speed = -3.5;
                right_speed = -2;
                avoid_obstacle_counter_right--;  // Decrease the time to move by 1
            }
            else if (avoid_obstacle_counter_left> 0)
            {
                // Put the motors in reverse and turn slightly
                left_speed = -2;
                right_speed = -3.5;
                avoid_obstacle_counter_left--;  // Decrease the time to move by 1
            }
            else if (deeznuts)
            {
                // Put the motors in reverse and turn slightly
                left_speed = 5;
                right_speed = -5;
                deeznuts--;  // Decrease the time to move by 1
            }
        }
        else 
        {
            // Update the data of the distance sensors
            for (i = 0; i < 2; i++)
                ds_values[i] = wb_distance_sensor_get_value(ds[i]);
            
            // // Update the data of the floor sensors
            // for (i = 0; i < 2; i++)
            //     fs_values[i] = wb_distance_sensor_get_value(fs[i]);

            // Update the data of the floor sensors
            for (i = 0; i < 2; i++)
            {
                fs_values[i] = wb_distance_sensor_get_value(fs[i]);
                printf("Value of %s : %d\n",fs_names[i],fs_values[i]);
            }
            //printf("Balls : %d\n",wb_distance_sensor_get_value(69));
                
            // Update the data of the light sensors
            for (i = 0; i < 3; i++)
                ls_values[i] = wb_light_sensor_get_value(ls[i]);
            
            ls_max = ls_values[0];
            light_index = 0;
            
            // Find the index of the light sensor detecting the most light and it's value
            for (i = 1; i < 3; i++) 
            {
                if (ls_values[i] > ls_max) {
                ls_max = ls_values[i];
                light_index = i;
                }
            }
            // Print the sensor detecting the most light and it's value
            //printf("Light Sensor with more light = %d value: %d\n", light_index, ls_values[light_index]);
            // If the light is on the left
            if(light_index == 0)
            {
                // Go left
                left_speed = 0;
                right_speed = 2.0;
            }
            // If the light is on the right
            else if (light_index == 1)
            {
                // Go right
                left_speed = 2.0;
                right_speed = 0;
            }
            // If the light is straight ahead go super fast
            else if (light_index == 2)
            {
                // Go straight (faster)
                left_speed = 3.0;
                right_speed = 3.0;
            }
            
            // If there is something on the left (wall or no more floor)
            if (ds_values[0] < 950.0 || fs_values[0] < 20.0)
                avoid_obstacle_counter_right = 50;  // Go backward right for the specified time
            // If there is something on the right (wall or no more floor)
            else if (ds_values[1] < 950.0  || fs_values[1] < 20.0)
                avoid_obstacle_counter_left = 50;  // Go backward left for the specified time
        
            if(wb_distance_sensor_get_value(69) >= 40)
            {
                //printf("damn : %d\n",wb_distance_sensor_get_value(69));
                // _waitcnt(_clockfreq() / 1000 * 1000 + _cnt()); // Wait 1000 ms
                if((wb_distance_sensor_get_value(69)+wb_distance_sensor_get_value(69))/2 >= 35)
                {
                    deeznuts = 5;
                }
            }
        }

        // For the blue LED
        //  Vitesse moyenne = (3 + |-1|) / 2 = 2 rad/s
        //  Intensité lumineuse = Vitesse moyenne / Vitesse maximale * 100% = 2/4 *100% = 50%
        avg_speed = (abs(left_speed) + abs(right_speed)) / 2;
        led_brightness = avg_speed;
        
        // Turn the Blue LED with the specified brightness
        wb_led_set(leds[3], 0x0000ff & led_brightness);
        // printf("Moyenne = %d \n", avg_speed);
        // printf("Blue LED brightness = %d \n", led_brightness);

        // For the left LED
        // printf("Left LED = ");
        if(left_speed >= 0)
        {
            // Turn the green led on
            wb_led_set(leds[0], 0x007f00);
            // printf("Forward Mode\n");
        }
        else
        {
            // Delay every 1/4 sec more or less
            if(counter%2 == 0)
            {
                // Invert the led (Off or red)
                if(wb_led_get(leds[0]))
                    wb_led_set(leds[0], 0);
                else
                    wb_led_set(leds[0], 0xff0000);
            }
            // printf("Backward Mode\n");
        }

        // For the right LED
        // printf("Right LED = ");
        if(right_speed >= 0)
        {
            wb_led_set(leds[2], 0x007f00);
            // printf("Forward Mode\n");
        }
        else
        {
            // Delay every 1/4 sec more or less
            if(counter%2 == 0)
            {
                if(wb_led_get(leds[2]))
                    wb_led_set(leds[2], 0);
                else
                    wb_led_set(leds[2], 0xff0000);
            }
            // printf("Backward Mode\n");
        }

        // For the LED in the middle
        if(abs(left_speed) == abs(right_speed))
            wb_led_set(leds[1], 0x00ff00);
        else
            wb_led_set(leds[1], 0);

        // Apply the speed to the motors
        wb_motor_set_velocity(wheels[0], left_speed);
        wb_motor_set_velocity(wheels[1], right_speed);
        
        // Update the counter
        counter++;
        //printf("Counter : %d\n",_cnt());
    }
    wb_robot_cleanup();
    return 0;  // EXIT_SUCCESS
}
