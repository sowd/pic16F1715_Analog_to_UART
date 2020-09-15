/* 
 * File:   main.c
 * Author: owd
 *
 * Created on 2020/09/14, 23:45
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include "config.h"
#include "analog_serial.h"


void main(){
    // Internal clock = 8MHzÅ@x 4=32MHz (should match _XTAL_FREQ in config.h)
    OSCCON = 0b01110000 ;

    /*
    // Bank A
    A0 : RA0 : Pin 13 (Occupied for Serial)
    A1 : RA1 : Pin 12 (Occupied for Serial)
    A2 : RA2 : Pin 11
    A3 : RA4 : Pin 3
    // Bank C
    A4 : RC0 : Pin 10
    A5 : RC1 : Pin 9
    A6 : RC2 : Pin 8
    A7 : RC3 : Pin 7  
    */
    // Initializes serial port and analog pins, splitted to bank A/C.
    // Never specify A0,A1, because those pins are used for serial communication
    init(9600, A2|A3 , A4|A5|A6|A7); // Enable all pins
    
    char valStr[16];
    while(1){
        unsigned char c;
        c = serial_getch();
        
        // c should be '2' to '7' that corresponds to Analog ID
        unsigned int val = analogRead(c-'0');
        sprintf(valStr,"%c:%d,",c,val);
        // sprintf(valStr,"%c:%d\r\n",c,val); // Terminal friendly output
        serial_print(valStr);
    }
}
