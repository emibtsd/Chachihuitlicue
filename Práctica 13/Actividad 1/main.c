#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//=============================================================================
// CONFIGURACIÓN DE BITS DE CONFIGURACIÓN (FUSES)
//=============================================================================
#pragma config FOSC = HS        // Oscilador de alta velocidad (Cristal de 8 MHz)
#pragma config WDTE = OFF       // Watchdog Timer desactivado
#pragma config PWRTE = OFF      // Power-up Timer desactivado
#pragma config BOREN = ON       // Brown-out Reset activado
#pragma config LVP = OFF        // Programación de bajo voltaje desactivada
#pragma config CPD = OFF        // Protección de EEPROM desactivada
#pragma config WRT = OFF        // Protección de escritura de Flash desactivada
#pragma config CP = OFF         // Protección de código desactivada

//=============================================================================
// DEFINICIONES
//=============================================================================
#define _XTAL_FREQ 8000000      // Frecuencia del cristal (8 MHz)

void ADC_Init(void) {
    ANSEL = 0x01;            
    ANSELH = 0x00;             
    TRISAbits.TRISA0 = 1;       
    
    ADCON0 = 0x01;              
    ADCON1 = 0x80;             
}

unsigned int ADC_Read(void) {
    __delay_us(20);           
    ADCON0bits.GO_nDONE = 1;  
    
    while(ADCON0bits.GO_nDONE); 
    
    return ((ADRESH << 8) + ADRESL); 
}

void main(void) {
    TRISCbits.TRISC2 = 0;   
    PR2 = 249;                  
    CCP1CON = 0x0C;            
    T2CON = 0x05;            
    
    ADC_Init();            
    
    unsigned int lectura_pot = 0;
  
    while(1) {
        
        lectura_pot = ADC_Read();
        
        CCPR1L = lectura_pot / 4; 
        
        __delay_ms(5); 
    }
}