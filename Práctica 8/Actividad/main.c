#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lcd.h"

// CONFIG
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 8000000

void LCD_Create_Char(unsigned char location, unsigned char charmap[]) {
    location &= 0x07;                 
    LCD_Cmd(0x40 + (location * 8));   

    for(unsigned char i = 0; i < 8; i++) {
        LCD_putc(charmap[i]);         
    }
}

unsigned char HAPPY[8] = {
    0b00000,
    0b01010,
    0b01010,
    0b00000,
    0b10001,
    0b01110,
    0b00000,
    0b00000
};

unsigned char SAD[8] = {
    0b00000,
    0b01010,
    0b01010,
    0b00000,
    0b01110,
    0b10001,
    0b00000,
    0b00000
};

void mostrarMensaje(unsigned char estado){
    LCD_Clear();

    if(estado == 0){
        LCD_Set_Cursor(0,0);
        LCD_putc(0);
    }
    else{
        LCD_Set_Cursor(0,0);
        LCD_putc(1);
    }
}

void main(void){
    LCD lcd = {&PORTC, 2,3,4,5,6,7};

    ANSEL = 0;
    ANSELH = 0;

    TRISBbits.TRISB0 = 1;
    OPTION_REGbits.nRBPU = 0;

    LCD_Init(lcd);

    LCD_Create_Char(0, HAPPY);
    LCD_Create_Char(1, SAD);

    unsigned char estado = 0;

    mostrarMensaje(estado);

    while(1){

        if(PORTBbits.RB0 == 0){
            __delay_ms(20);

            if(PORTBbits.RB0 == 0){
                estado = !estado;

                mostrarMensaje(estado);

                while(PORTBbits.RB0 == 0);
                __delay_ms(20);
            }
        }
    }
}