/* 
 * Created from labyrinthe.binary
 * 
 * by Spin to C Array Converter, version 5.0
 */
#ifndef ADCARRAY_H
#define	ADCARRAY_H

#define labyrinthe_CLOCKFREQ  80000000
#define labyrinthe_CLOCKMODE  0x6F

#define labyrinthe_ARRAYTYPE 0 // array contains PASM program
#define labyrinthe_PROG_SIZE  188 // bytes

extern unsigned long labyrinthe_array[];

#endif	/* ADCARRAY_H */
