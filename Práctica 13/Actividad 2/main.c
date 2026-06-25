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

#define IN1 PORTBbits.RB0     
#define IN2 PORTBbits.RB1   
#define BTN_DER PORTBbits.RB2  
#define BTN_IZQ PORTBbits.RB3   


void PWM_Init(void) {
    TRISCbits.TRISC2 = 0;     
    PR2 = 249;            
    CCP1CON = 0x0C;  
    T2CON = 0x05;           
}

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
    TRISBbits.TRISB0 = 0;       
    TRISBbits.TRISB1 = 0;       
    TRISBbits.TRISB2 = 1;       
    TRISBbits.TRISB3 = 1;      
    
    OPTION_REGbits.nRBPU = 0;
    
    PORTBbits.RB0 = 0;
    PORTBbits.RB1 = 0;
    
    PWM_Init();      
    ADC_Init();           
    

    while(1) {

        CCPR1L = ADC_Read() / 4; 
        
        if (BTN_DER == 0 && BTN_IZQ == 1) {
            IN1 = 1;
            IN2 = 0;
        }
        else if (BTN_IZQ == 0 && BTN_DER == 1) {
            IN1 = 0;
            IN2 = 1;
        }
        else {
            IN1 = 0;
            IN2 = 0;
        }
    }
}