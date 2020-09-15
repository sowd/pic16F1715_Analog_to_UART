/* 
 * File:   analog_serial.h
 * Author: owd
 *
 * Created on 2020/09/15, 7:41
 */

#ifndef SERIAL_H
#define	SERIAL_H

#ifdef	__cplusplus
extern "C" {
#endif

#define _XTAL_FREQ 32000000     //ÉNÉçÉbÉN32MHz

    
// Bank A
#define A0 0b00000001 // RA0 : Pin 13 (Occupied for Serial)
#define A1 0b00000010 // RA1 : Pin 12 (Occupied for Serial)
#define A2 0b00000100 // RA2 : Pin 11
#define A3 0b00010000 // RA4 : Pin 3
// Bank C
#define A4 0b00000001 // RC0 : Pin 10
#define A5 0b00000010 // RC1 : Pin 9
#define A6 0b00000100 // RC2 : Pin 8
#define A7 0b00001000 // RC3 : Pin 7    

// portA: A0-A3 , portC: A4-A7
void init(unsigned long baudrate,unsigned char portA,unsigned char portC);

unsigned int analogRead(unsigned char pin);

void serial_putch(unsigned char byte);
unsigned char serial_getch();
//void serial_init(unsigned long BR);
void serial_print(char* str);



#ifdef	__cplusplus
}
#endif

#endif	/* SERIAL_H */

