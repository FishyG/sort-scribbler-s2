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
            for (j = 0; j < 8; j++)
            {
                // If the intensity is greater than i turn the LED "on" else turn it "off"
                _outa(LED_DATA, (intensite_del[j] > i) ? LED_DATA : 0);
                
                // Send a pulse on the clock pin
                _outa(LED_CLK,LED_CLK);
                _outa(LED_CLK,0);
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
    // printf("Array : ");   
    // for (i = 0; i < 8; i++)
    // {
    //     printf("%d ",intensite_del[i]);
    // }
    // printf("\n");
    
    if(led == 0)
    {
        if(color > 0xff00)
        {
            intensite_del[3] = ((color >> 16)/51);
            intensite_del[4] = 0;
        }
        else
        {
            intensite_del[3] = 0;
            intensite_del[4] = ((color >> 8)/51);
        }
    }
    else if(led == 1)
    {
        intensite_del[3] = (color/51);
    }
    // For the right led
    else if(led == 2)
    {
        if(color > 0xff00)
        {
            intensite_del[5] = ((color >> 16)/51);
            intensite_del[6] = 0;
        }
        else
        {
            intensite_del[5] = 0;
            intensite_del[6] = ((color >> 8)/51);
        }
            
    }
    else if(led == 3)
    {
        //intensite_del[] = (color/51);

    }
}

int wb_led_get(short tag)
{
    int return_value = 0;

    if(tag == 0)
    {
        return_value = intensite_del[3] | intensite_del[4]  ;
    }
    else if(tag == 1)
    {
        
    }
    // For the right led
    else if(tag == 2)
    {
        return_value = intensite_del[5] | intensite_del[6];
    }
    else if(tag == 3)
    {
        return_value = intensite_del[7];

    }
    return return_value;
}
