/* 
 * @file    music.h
 * @author  Jessy Grimard-Maheu
 * @date    10 Avril 2023
 * @brief   .h de music.c
 * @version 1.0 : Version initiale
 */

#ifndef MUSIC_H
#define	MUSIC_H

#define C  956      // Do
#define Cd 902
#define D  851      // ré
#define Dd 804
#define E  758      // Mi
#define F  716      // Fa
#define Fd 676
#define G  638      // Sol
#define Gd 602
#define A  568      // La
#define Ad 536
#define B  506      // Si

// Prototypes
void play(char* music, unsigned int tempo, int pin);
void note(unsigned int note, unsigned int tempsms);
void wait(unsigned int tempsms);

void Rick(void);
void Mario(void);
void StarWars(void);
// void HarryPotter(void);
// void LaFamilleTortue(void);

#endif	/* MUSIC_H */
