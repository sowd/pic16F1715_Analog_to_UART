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
    // �ǎ�l�͉E�񂹁AA/D�ϊ��N���b�N��FOSC/8�AVDD�����t�@�����X��
    ADCON1 = 0b10010000 ;

    
    // Serial pin setting.
    /* TX RX pin assignments*/
    RA0PPS = 0x14;            //TX to RA0
    RXPPS = 0x01;             //RA1 to RX
   
    TX1STA = 0x24;   //SYNC=0 TXEN = 1 BRGH = 1
    BRG16 = 1;       //BRG 16bit mode
    RC1STA = 0x90;   //asynchronous, continuous recv �񓯊��A�p����M��
    unsigned int X= _XTAL_FREQ/baudrate/4 - 1;
    SP1BRGH = X / 256;
    SP1BRGL = X % 256;
}


unsigned int analogRead(unsigned char pin){
    ADCON0 = (unsigned char)( (pin << 2 ) | 1 );
    __delay_us(5) ;
    
    unsigned int val;
     GO_nDONE = 1 ;         // PIC�ɃA�i���O�l�ǎ��J�n���w��
     while(GO_nDONE) ;      // PIC���ǎ�芮������܂ő҂�
     val = ADRESH ;        // PIC�͓ǎ�����l��ADRESH��ADRESL�̃��W�X�^�[�ɃZ�b�g����
     val = ( val << 8 ) | ADRESL ;  // 10�r�b�g�̕���\�͂ł�

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
