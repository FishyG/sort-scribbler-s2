/* 
 * @file    led.h
 * @author  Jessy Grimard-Maheu
 * @date    15 Mars 2023
 * @brief   .h de led.c
 * @version 1.0 : Version initiale
 */

#ifndef LED_H
#define	LED_H

// For the shift register
#define LED_CLK 1 << 8
#define LED_DATA 1 << 7

//prototype
// void del_shift(char data_del[]);
void del_shift_pwm(void);

void wb_led_set(short led, int color);

int wb_led_get(short tag);

#endif	/* LED_H */
