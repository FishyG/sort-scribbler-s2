/* 
 * @file    distance_sensors.c
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   
 * @version 1.0 : Version initiale
 */

#include "led.h"
#include "robot.h"
#include "stdio.h"
#include "propeller.h"

char intensite_del[8] = {0,0,0,0,0,0,0,0};
// extern char intensite_del[];

// Function controlling the shift register (LEDs)
void del_shift_pwm(void)
{
    int i = 0;
    int j = 0;
    _dira(LED_CLK, LED_CLK);
    _dira(LED_DATA, LED_DATA);

    while(1)
    {
        while(i < 5)
        {
            for (j = 7; j >= 0; j--)
            {
                // If the intensity is greater than i turn the LED "on" else turn it "off"
                _outa(LED_DATA, (intensite_del[j] > i) ? LED_DATA : 0);
                
                // Send a pulse on the clock pin
                // _outa(LED_CLK,LED_CLK);
                // _outa(LED_CLK,0);

                // Same as _outa but a tiny bit faster
                PASM("or outa, #256");    // set LED_CLK pin high
                PASM("andn outa, #256");  // set LED_CLK pin low
            }
            i++;
            _waitcnt(_clockfreq()/500 +_cnt()); // Delay 10 ms

            // printf("Array : ");   
            // for (i = 0; i < 8; i++)
            // {
            //     printf("%d ",intensite_del[i]);
            // }
            // printf("\n");
        }
        i = 0;
    }
}

void wb_led_set(short led, int color)
{   
    int i = 0;
    printf("Array : ");   
    for (i = 0; i < 8; i++)
    {
        printf("%d ",intensite_del[i]);
    }
    printf("\n");
    
    // For the left led
    if(led == 0)
    {
        if(color > 0xff00)
        {
            intensite_del[2] = ((color >> 16)/51);
            intensite_del[3] = 0;
        }
        else
        {
            intensite_del[2] = 0;
            intensite_del[3] = ((color >> 8)/51);
        }
    }
    // For the center led
    else if(led == 1)
    {
        if(color > 0xff00)
        {
            intensite_del[6] = ((color >> 16)/51);
            intensite_del[7] = 0;
        }
        else
        {
            intensite_del[6] = 0;
            intensite_del[7] = ((color >> 8)/51);
        }
    }
    // For the right led
    else if(led == 2)
    {
        if(color > 0xff00)
        {
            intensite_del[4] = ((color >> 16)/51);
            intensite_del[5] = 0;
        }
        else
        {
            intensite_del[4] = 0;
            intensite_del[5] = ((color >> 8)/51);
        }
            
    }
    else if(led == 3)
    {
        intensite_del[0] = (color);
    }
}

int wb_led_get(short tag)
{
    int return_value = 0;


    if(tag == 0)
    {
        return_value = intensite_del[2] | intensite_del[3];
    }
    else if(tag == 1)
    {
        return_value = intensite_del[6] | intensite_del[7];
    }
    // For the right led
    else if(tag == 2)
    {
        return_value = intensite_del[4] | intensite_del[5];
    }
    else if(tag == 3)
    {
        return_value = intensite_del[0];

    }
    return return_value;
}
