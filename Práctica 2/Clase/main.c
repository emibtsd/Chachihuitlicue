#include <xc.h>         // Biblioteca principal del compilador XC8

//=============================================================================
// CONFIGURACI N DE BITS DE CONFIGURACI N (FUSES)
//=============================================================================

// Selecci n de oscilador (usar XT si estas usando un cristal de 4 MHz)
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

unsigned char patron[8]= {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81};

        
void main(void){
    TRISB= 0b00000000;     // Filas
    TRISD= 0b00000000;     // Columnas
    PORTB= 0;              // Reset filas
    PORTD= 0;              // Reset columnas
    
    while (1){
        for(char i= 0; i<8; i++){
            PORTB= 1<<i;           // Hace que el un 1 en binario se recorra a la izquierda 1 en 1
            PORTD= ~patron[i];
            __delay_ms(5);
        }
    }
}