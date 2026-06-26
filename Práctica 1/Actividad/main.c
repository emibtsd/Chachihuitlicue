#include <xc.h>

#pragma config FOSC = XT        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config BOREN = ON       
#pragma config LVP = OFF        
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF         

#define _XTAL_FREQ 8000000      

void main(void){
    TRISD = 0x00;
    PORTD = 0x00;
    
    while(1){       
        PORTD = 0x01;
        __delay_ms(150);
        PORTD = 0x02;
        __delay_ms(150);
        PORTD = 0x04;
        __delay_ms(150);
        PORTD = 0x08;
        __delay_ms(150);
        PORTD = 0x10;
        __delay_ms(150);
        PORTD = 0x20;
        __delay_ms(150);
        PORTD = 0x40;
        __delay_ms(150);
        PORTD = 0x80;
        __delay_ms(150);
        PORTD = 0x40;
        __delay_ms(150);
        PORTD = 0x20;
        __delay_ms(150);
        PORTD = 0x10;
        __delay_ms(150);
        PORTD = 0x08;
        __delay_ms(150);
        PORTD = 0x04;
        __delay_ms(150);
        PORTD = 0x02;
        __delay_ms(150);
    }
}