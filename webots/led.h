/* 
 * @file    led.h
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   .h de led.c (voir led.c pour le brief)
 * @version 1.0 : Version initiale
 */

#ifndef LED_H
#define	LED_H

// For the shift register
#define LED_CLK 1 << 8  // Define the clock pin of the shift register
#define LED_DATA 1 << 7 // Define the data pin of the shift register

//prototype
/**
    @brief Fonction permettant de controller le registre à décalage
*/
void del_shift_pwm(void);

/**
    @brief Fonction pour définir les couleurs des DELs
    @param led Id de la DEL.
    @param color Couleur de la DEL.
*/
void wb_led_set(short led, int color);

/**
    @brief Fonction pour vérifier la couleur des DELs
    @param tag Id de la DEL.
    @return La couleur de la DEL.
*/
int wb_led_get(short tag);

#endif	/* LED_H */
