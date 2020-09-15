/* 
 * File:   analog_serial.c
 * Author: owd
 *
 * Created on 2020/09/14, 23:45
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include "config.h"
#include "analog_serial.h"

// portA: A0-A3 , portC: A4-A7
// http://zattouka.net/GarageHouse/micon/MPLAB/16F1705/VRtoLED2/VRtoLED2.htm
// https://blog.goo.ne.jp/jh7ubc/e/e7737c8c0b2bf4f6dc2d020318758bd0
void init(unsigned long baudrate,unsigned char portA,unsigned char portC){
    // Set analog pins. A0,A1 are used for UART
    ANSELA = portA & 0b11111100 ;
    ANSELC = portC ;
    // Set input pins. A0 is always output while A1 is input.
    TRISA  = (portA & 0b11111100) | A1 ;
    TRISC  = portC ;
    PORTA  = 0b00000000 ;      // Clear PORTA
    PORTC  = 0b00000000 ;      // Clear PORTC
    
    // Analog read basic setting.
    // 読取値は右寄せ、A/D変換クロックはFOSC/8、VDDをリファレンスに
    ADCON1 = 0b10010000 ;

    
    // Serial pin setting.
    /* TX RX pin assignments*/
    RA0PPS = 0x14;            //TX to RA0
    RXPPS = 0x01;             //RA1 to RX
   
    TX1STA = 0x24;   //SYNC=0 TXEN = 1 BRGH = 1
    BRG16 = 1;       //BRG 16bit mode
    RC1STA = 0x90;   //asynchronous, continuous recv 非同期、継続受信可
    unsigned int X= _XTAL_FREQ/baudrate/4 - 1;
    SP1BRGH = X / 256;
    SP1BRGL = X % 256;
}


unsigned int analogRead(unsigned char pin){
    ADCON0 = (unsigned char)( (pin << 2 ) | 1 );
    __delay_us(5) ;
    
    unsigned int val;
     GO_nDONE = 1 ;         // PICにアナログ値読取り開始を指示
     while(GO_nDONE) ;      // PICが読取り完了するまで待つ
     val = ADRESH ;        // PICは読取った値をADRESHとADRESLのレジスターにセットする
     val = ( val << 8 ) | ADRESL ;  // 10ビットの分解能力です

     return val ;
}

void serial_putch(unsigned char byte){
    while(!TXIF);
    TX1REG = byte;
}
 
unsigned char serial_getch(){
    while(!RCIF);
    return RC1REG;
}

void serial_print(char* str){
    for( int i=0;1;++i ){
        if( str[i] == 0 ) break;
        serial_putch((unsigned char)(str[i]));
    }
}
