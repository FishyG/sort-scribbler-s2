/*
Transfert de la librairie Synth.spin en langage C (synth.h, synth.c) par Pierre Bergeron Automne 2013
{{
*****************************************
* Frequency Synthesizer demo v1.2       *
* Author: Beau Schwabe, Thomas E. McInnes*
* Copyright (c) 2007 Parallax           *
* See end of file for terms of use.     *
*****************************************
  Original Author: Chip Gracey
  Modified by Beau Schwabe
  Modified by Thomas E. McInnes
*****************************************
}}
{
Revision History:
                  Version 1.0   -    original file created

                  Version 1.1   -    For Channel "B" there was a typo in the 'Synth' object
                                     The line that reads...
                                     DIRB[Pin]~~                        'make pin output
                                     ...should read...
                                     DIRA[Pin]~~                        'make pin output

                  Version 1.2   -    Silence routine added

                  Version 1.3   -    Silence routines updated and made easier to use
*/

#include "catalina_cog.h"
#include "propeller.h"
#include "synth.h"

/*
Configuration des compteurs CTRA/CTRB pour la génération d'un signal.

Entrées :
        - CTR_AB : 'A' pour compteur CTRA ou 'B' pour CTRB
        - Pin : Broche utilisée pour la génération du signal
        - Freq : Fréquence demandée

Sortie :
        - Aucune
*/
void synth(long CTR_AB, long Pin, long Freq)
{
    long s, d, ctr, frq;

    Freq = (Freq < 0) ? 0 : (Freq > 128000000) ?  128000000 : Freq ;     //limit frequency range



    if(Freq < 500000)                   //if 0 to 499_999 Hz,
    {
        ctr = 0x04 << 26;               //..set NCO mode
        s = 1;                          //..shift = 1
    }
    else                                //if 500_000 to 128_000_000 Hz,
    {
        ctr = 0x02 << 26;              //..set PLL mode
        d = 1;                          //determine PLLDIV
        d <<= ((Freq - 1) / 1000000) - 1;
        s = 4 - d;                      //determine shift
        ctr |= d << 23;                 //set PLLDIV
    }


    frq = fraction(Freq, CLKFREQ, s);   //Compute FRQA/FRQB value
    ctr |= Pin;                         //set PINA to complete CTRA/CTRB value

    if (CTR_AB == 'A')
    {
        CTRA = ctr;                     //set CTRA
        FRQA = frq;                     //set FRQA
    }

    if( CTR_AB == 'B')
    {
        CTRB = ctr;                      //set CTRB
        FRQB = frq;                      //set FRQB
    }
    _dira(1<<Pin,1<<Pin);                //make pin output

}


/*
Arrêt de la génération du signal pour le compteur CTRA

Entrée :
        - Pin : Broche utilisée pour la génération du signal

Sortie :
        - Aucune
*/
void silence_a(long Pin)
{
    synth ('A', Pin, 0);
}

/*
Arrêt de la génération du signal pour le compteur CTRB

Entrée :
        - Pin : Broche utilisée pour la génération du signal

Sortie :
        - Aucune
*/

void silence_b(long Pin)
{
    synth ('B', Pin, 0);
}

/*
Calcul de la fréquence pour le registre FRQA/FRQB en fonction de l'horloge du système

Entrées :
        - a : Fréquence du signal
        - b : Fréquence de l'horloge du système
        - s : Décalage en fonction du diviseur pour le PLL

Sortie :
        - Valeur du registre FRQA/FRQB

*/
int fraction(long a, long b, long shift)
{
    char i;
    long f;

    if (shift > 0)                      //if shift, pre-shift a or b left
        a <<= shift;                    //to maintain significant bits while

    if (shift < 0)                      //insuring proper result
        b <<= -shift;

    for(i = 0; i<32; i++)               //perform long division of a/b
    {
        f <<= 1;
        if(a >= b)
        {
            a -= b;
            f++;
        }
        a <<= 1;
    }
    return f;
}

/*
┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│                                                   TERMS OF USE: MIT License                                                  │
├──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation    │
│files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,    │
│modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software│
│is furnished to do so, subject to the following conditions:                                                                   │
│                                                                                                                              │
│The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.│
│                                                                                                                              │
│THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE          │
│WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR         │
│COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,   │
│ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                         │
└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
*/


