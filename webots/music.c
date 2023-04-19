/* 
 * @file    music.c
 * @author  Pierre  Bergeron, Jessy Grimard-Maheu
 * @date    10 Avril 2023
 * @brief   Joue de la musique (fait de Beep et des Boop). Fait par Pierre Bergeron. et modifier (légèrement) par Jessy.
 * @version 1.0 : Version initiale
 */

#include "catalina_cog.h"
#include "propeller.h"
#include "music.h"


int BLANCHE = 2000;
int NOIRE   = 1000;
int TRIO    =  666;
int CROCHE  =  500;
int BUZZER  = 0000; // Pour le buzzer

void play(char* music, unsigned int tempo, int pin)
{
    int i;

    BUZZER = (1<<pin);

    BLANCHE = 120000/tempo;
    NOIRE   =  60000/tempo;
    TRIO    =  40000/tempo;
    CROCHE  =  30000/tempo;

    printf("Playing %s\n", music);
    if (strcmp(music, "Mario") == 0){
        Mario();
    } else if (strcmp(music, "StarWars") == 0){
        StarWars();
    // } else if (strcmp(music, "La famille tortue") == 0){
    //     LaFamilleTortue();
    // } else if (strcmp(music, "Harry Potter") == 0){
    //     HarryPotter();
    } else if (strcmp(music, "Rick") == 0){
        Rick();
    }

    // wait(BLANCHE);wait(BLANCHE);wait(BLANCHE);wait(BLANCHE);
}

void note(unsigned int note, unsigned int tempsms){
    unsigned int j, nombre_de_cycle=0;
    _dira(BUZZER, BUZZER);
    nombre_de_cycle = (500*tempsms)/note;   // = (1000*tempsms) / (2*note)
    for (j=0; j<nombre_de_cycle; j++)
    {
        _outa(BUZZER, BUZZER);
        _waitcnt(((_clockfreq()/1000000) * note) + _cnt());
        _outa(BUZZER, 0);
        _waitcnt(((_clockfreq()/1000000) * note) + _cnt());
    }
    wait(10);
}

void wait(unsigned int tempsms){
    if(tempsms>0)
        _waitcnt(((_clockfreq()/1000) * tempsms) + _cnt());
}

void Mario(void){
    note(C/2, CROCHE);
    note(C/2, CROCHE);wait(CROCHE);
    note(C/2, CROCHE);wait(CROCHE);
    note(A, CROCHE);
    note(C/2, NOIRE);
    note(D/2, NOIRE);wait(NOIRE);
    note(G, NOIRE);wait(NOIRE);
    // note(C/2, NOIRE);wait(CROCHE);
    // note(G, NOIRE);wait(CROCHE);
    // note(E, NOIRE);wait(CROCHE);
    // note(A, CROCHE);wait(CROCHE);
    // note(B, NOIRE);
    // note(Ad, CROCHE);
    // note(A, NOIRE);
    // note(G, TRIO);
    // note(E/2, TRIO);
    // note(G/2, TRIO);
    // note(A/2, NOIRE);
    // note(F/2, CROCHE);
    // note(G/2, CROCHE);wait(CROCHE);
    // note(E/2, NOIRE);
    // note(C/2, CROCHE);
    // note(D/2, CROCHE);
    // note(B, NOIRE);wait(CROCHE);
    // note(C/2, NOIRE);wait(CROCHE);
    // note(G, NOIRE);wait(CROCHE);
    // note(E, NOIRE);wait(CROCHE);
    // note(A, CROCHE);wait(CROCHE);
    // note(B, NOIRE);
    // note(Ad, CROCHE);
    // note(A, NOIRE);
    // note(G, TRIO);
    // note(E/2, TRIO);
    // note(G/2, TRIO);
    // note(A/2, NOIRE);
    // note(F/2, CROCHE);
    // note(G/2, CROCHE);wait(CROCHE);
    // note(E/2, NOIRE);
    // note(C/2, CROCHE);
    // note(D/2, CROCHE);
    // note(B, NOIRE);wait(CROCHE);wait(NOIRE);
    // note(G/2, CROCHE);
    // note(Fd/2, CROCHE);
    // note(F/2, CROCHE);
    // note(Dd/2, NOIRE);
    // note(E/2, CROCHE);wait(CROCHE);
    // note(Gd, CROCHE);
    // note(A, CROCHE);
    // note(C/2, CROCHE);wait(CROCHE);
    // note(A, CROCHE);
    // note(C/2, CROCHE);
    // note(D/2, CROCHE);wait(NOIRE);
    // note(G/2, CROCHE);
    // note(Fd/2, CROCHE);
    // note(F/2, CROCHE);
    // note(Dd/2, NOIRE);
    // note(E/2, CROCHE);wait(CROCHE);
}

void StarWars(void){
    note(G, CROCHE/2);
    note(G, CROCHE/2);
    note(G, NOIRE+CROCHE);
    note(G, CROCHE);
    note(G, CROCHE);
    note(G, CROCHE);

    note(G, CROCHE);
    note(D, CROCHE);
    note(C/2, CROCHE);
    note(E, CROCHE);
    note(D, CROCHE);
    note(C/2, CROCHE);
    note(D/2, CROCHE);
    note(C/2, CROCHE);
    note(G, CROCHE);
    note(G, CROCHE);
    note(D, CROCHE);
    note(C/2, CROCHE);

    note(D/2, CROCHE);
    note(C/2, CROCHE);
    note(G, CROCHE);
    note(D, CROCHE);
    note(C/2, CROCHE);
    note(D/2, CROCHE);
    note(G, CROCHE/2);
    note(G, CROCHE/2);
    note(G, CROCHE);
}
