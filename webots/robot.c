/* 
 * @file    robot.c
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   
 * @version 1.0 : Version initiale
 */

#include <catalina_cog.h>
#include <stdio.h> 
#include <string.h>
//#include "adcArray.h"
#include "led.h"
#include "robot.h"
#include "motor.h"

// Variable for the analog conversion
long sigma = 0;

unsigned long labyrinthe_array[] =
{
    0xa0fff401, 0x58fff048, 0x54fff01a, 0x50fff01b, 
    0xa0bfec2b, 0xa0bc5df0, 0x68bfec2c, 0xa0bc5e29, 
    0xa0bc6029, 0x28fc6001, 0x64bfe82c, 0x5cfc421e, 
    0x5cfc5022, 0xa0bc6631, 0x68bfe82c, 0x5cfc421e, 
    0x5cfc5022, 0x84bc6233, 0x873c622a, 0x5c680017, 
    0x94bc5e30, 0x2afc6001, 0x5c54000a, 0x64bfec2c, 
    0x5cfc5022, 0x84bc6233, 0x44bc622a, 0x40fc6200, 
    0x083c622e, 0x5c7c0018, 0xa0bc65f1, 0x80bc642d, 
    0xf8fc6400, 0x5c7c0000, 0xa0bc65f1, 0x80fc6410, 
    0xf8bc642f, 0xa4bc63fc, 0xf8fc6400, 0x80bc63fc, 
    0x5c7c0000, 0x00000200, 0x000000ff, 0x04000000, 
    0x00000002, 0x00009c40, 0x00000000
};

int wb_robot_get_device(const char* device)
{
    int return_value = 0;

    //printf("%s\n",device);
    if (strcmp(device,"ls_left") == 0)
    {
        return_value = 0;
    }
    else if (strcmp(device,"ls_right") == 0)
    {
        return_value = 1;
    }
    else if (strcmp(device,"ls_center") == 0)
    {
        return_value = 2;
    }
    else if (strcmp(device,"led_0") == 0)
    {
        return_value = 0;
    }
    else if (strcmp(device,"led_1") == 0)
    {
        return_value = 1;
    }
    else if (strcmp(device,"led_2") == 0)
    {
        return_value = 2;
    }
    else if (strcmp(device,"led_3") == 0)
    {
        return_value = 3;
    }
    else if (strcmp(device,"wheel1") == 0)
    {
        return_value = 0;
    }
    else if (strcmp(device,"wheel2") == 0)
    {
        return_value = 1;
    }
    

    return return_value;
}

int wb_robot_init()
{
    unsigned long stack_pwm_motor[150];  // Stack pour le cog qui exécutera fct_pwm0
    unsigned long stack_pwm_led[150]; // Stack pour le cog qui exécutera fct_pwm1

    printf("Starting up... \n");
    _dira(0xf << 22, 0xf << 22);
    _outa(0xf << 22, 0);
    printf("ADC started on cog %d\n",_coginit((long)&sigma >> 2, (int)labyrinthe_array >> 2, ANY_COG)); // Start the ADC on a cog
    printf("Motor PWM started on cog %d\n",_coginit_C(&fct_pwm_all, &stack_pwm_motor[150])); // Start the pwm 0 on a cog
    printf("LED PWM started on cog %d\n",_coginit_C(&del_shift_pwm, &stack_pwm_led[150])); // Start the pwm 0 on a cog
    // _outa(1 << MUX_SELECT, 0);
    // _outa(1 << MUX_CHANNEL2, 1 << MUX_CHANNEL2);
    // _waitcnt(_clockfreq()/10 +_cnt()); // Delay 100 ms
    printf("Exiting robot init\n");
    return 0;
}

void wb_robot_cleanup(void)
{

}

int wb_robot_step(int duration)
{
    
    return duration;
}

int step_counter(int counter)
{
    
}
