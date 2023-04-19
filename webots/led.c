/**
 * @file    distance_sensors.c
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   Fichier .c contenant toutes les fonctions en lien avec le controle des
 *          DELs. La fonction del_shift_pwm doit être démarrer dans un cog. Les fonctions
 *          essaient de recréer le plus fidèlement possible les fonctions de webot.
 * @version 1.0 : Version initiale
 */

// Includes
#include "led.h"
#include "robot.h"
#include "stdio.h"
#include "propeller.h"

// Global variables
char intensite_del[8] = {0,0,0,0,0,0,0,0}; // Array with the brightness of each LED

/**
    @brief Fonction permettant de controller le registre à décalage
*/
void del_shift_pwm(void)
{
    int i = 0;
    int j = 0;
    
    _dira(LED_CLK, LED_CLK);    // Set the clock pin as an output
    _dira(LED_DATA, LED_DATA);  // Set the data pin as an output

    while(1)
    {
        // Iterate through the 5 levels of brightness
        while(i < 5)
        {
            // Set the brightness for each LED
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
        }
        i = 0;  // Reset the loop index i to 0 for the next iteration
    }
}

/**
    @brief Fonction pour définir les couleurs des DELs
    @param led Id de la DEL.
    @param color Couleur de la DEL.
*/
void wb_led_set(short led, int color)
{   
    // For the left LED
    if(led == 0)
    {
        // If the LED is red
        if(color > 0xffff)
        {
            intensite_del[2] = ((color >> 16)/51);  // Convert the html value to the value of the red LED
            intensite_del[3] = 0;   // Set the green pin to 0
        }
        // If the LED is green
        else
        {
            intensite_del[2] = 0;   // Set the red pin to 0
            intensite_del[3] = ((color >> 8)/51);   // Convert the html value to the value of the green LED
        }
    }
    // For the center LED
    else if(led == 1)
    {
        // If the LED is red
        if(color > 0xffff)
        {
            intensite_del[6] = ((color >> 16)/51);  // Convert the html value to the value of the red LED
            intensite_del[7] = 0;   // Set the green pin to 0
        }
        // If the LED is green
        else
        {
            intensite_del[6] = 0;   // Set the red pin to 0
            intensite_del[7] = ((color >> 8)/51);   // Convert the html value to the value of the green LED
        }
    }
    // For the right LED
    else if(led == 2)
    {
        // If the LED is red
        if(color > 0xff00)
        {
            intensite_del[4] = ((color >> 16)/51);  // Convert the html value to the value of the red LED
            intensite_del[5] = 0;   // Set the green pin to 0
        }
        // If the LED is green
        else
        {
            intensite_del[4] = 0;   // Set the red pin to 0
            intensite_del[5] = ((color >> 8)/51);   // Convert the html value to the value of the green LED
        }
            
    }
     // For the blue LED
    else if(led == 3)
    {
        // Set the value of the blue LED directly
        intensite_del[0] = (color);
    }
}

/**
    @brief Fonction pour vérifier la couleur des DELs
    @param tag Id de la DEL.
    @return La couleur de la DEL.
*/
int wb_led_get(short tag)
{
    int return_value = 0;

    // For the left LED
    if(tag == 0)
    {
        // Get the value of the left LED
        return_value = intensite_del[2] | intensite_del[3];
    }
    // For the middle LED
    else if(tag == 1)
    {
        // Get the value of the middle LED
        return_value = intensite_del[6] | intensite_del[7];
    }
    // For the right LED
    else if(tag == 2)
    {
        // Get the value of the right LED
        return_value = intensite_del[4] | intensite_del[5];
    }
    // For the blue LED
    else if(tag == 3)
    {
        // Get the value of the blue LED
        return_value = intensite_del[0];
    }
    return return_value; // return the state (color) of the LED
}
