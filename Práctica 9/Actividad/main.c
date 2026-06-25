#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lcd.h"

// Biblioteca principal del compilador XC8

//=============================================================================
// CONFIGURACIÓN DE BITS DE CONFIGURACIÓN (FUSES)
//=============================================================================

// Selección de oscilador (usar XT si estas usando un cristal de 8 MHz)
#pragma config FOSC = HS        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (disabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection (disabled)
#pragma config WRT = OFF        // Flash Program Memory Write Enable (disabled)
#pragma config CP = OFF         // Flash Program Memory Code Protection (disabled)

//=============================================================================
// DEFINICIONES
//=============================================================================

#define _XTAL_FREQ 8000000      // Frecuencia del oscilador (para __delay_ms y __delay_us)

volatile unsigned int tiempo = 0;
volatile unsigned int contador= 0;
char exec[10];

void ADC_Init(){
    ANSEL= 0x01;   // Establecer pines analogicos a digitales - este equivale a 0b00000001 solo ese 1 es analogico
    ADCON0= 0x81;
    ADCON1= 0x80;   
}

unsigned int ADC_read(){
    __delay_us(5);    // Para que el capacitor cargue y de buenas lectiras
    GO_nDONE= 1; 
    while(GO_nDONE);
    return((ADRESH<<8) + ADRESL);    //Recorre AH0 y AH1 a la izquierda y sobran 8 ceros que se llenan con al suma con todo ADRESL = palabra de 10 bits
}


void Timer0_Init(){
    OPTION_REG= 0x7;
    TMR0= 181; 
    T0IE= 1;
    GIE= 1;
}

void __interrupt() ISR(void){
    if (T0IF){
        contador++;
        if (contador > 100){
            tiempo++;
            contador = 0;
        }
        TMR0= 181;
        T0IF= 0; 
    }
}

void main(void){
    ADC_Init();
    Timer0_Init();
    LCD lcd= {&PORTC, 2, 3, 4, 5, 6, 7};
    LCD_Init(lcd);
    
    LCD_Clear();
    LCD_Set_Cursor(1, 11);
    LCD_putrs("00:00");
    
    LCD_Set_Cursor(0, 0);
    LCD_putrs("Voltaje: ");
    
    char buffer[10];
    
    while(1){
        LCD_Set_Cursor(1, 11);
        sprintf(exec, "%02u:%02u", tiempo/60, tiempo%60);
        LCD_putrs(exec);
        
        unsigned int adc_result = ADC_read();
        
        unsigned int volt= (adc_result * 50000) / 1023;
        unsigned int part_ent= volt / 10000; 
        unsigned int part_dec= volt % 10000;
        sprintf(buffer, "%u.%u", part_ent, part_dec);
        LCD_Set_Cursor(0, 9);
        LCD_putrs(buffer);
        
        __delay_ms(100);
    }
    
}