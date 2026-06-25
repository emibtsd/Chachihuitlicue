  #include <xc.h>         // Biblioteca principal del compilador XC8

//=============================================================================
// CONFIGURACIÓN DE BITS DE CONFIGURACIÓN (FUSES)
//=============================================================================

// Selección de oscilador (usar XT si estas usando un cristal de 4 MHz)
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

unsigned char patrones[6][8] = {
    {0x7F, 0x40, 0x40, 0x7F, 0x40, 0x40, 0x7F, 0x00}, // E
    {0x7C, 0x42, 0x42, 0x7C, 0x42, 0x42, 0x7C, 0x00}, // B
    {0x18, 0x24, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x00}, // A
    {0x7C, 0x42, 0x42, 0x7C, 0x48, 0x44, 0x42, 0x00}, // R
    {0x42, 0x66, 0x5A, 0x42, 0x42, 0x42, 0x42, 0x00}, // M
    {0x3E, 0x08, 0x08, 0x08, 0x08, 0x48, 0x30, 0x00}, // J
};

unsigned int t;

//=============================================================================
// FUNCIÓN PARA VOLTEAR LOS BITS (Arregla el efecto espejo)
//=============================================================================
unsigned char invertirByte(unsigned char b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

void main(void){
    TRISB= 0b00000000;     // Filas
    TRISD= 0b00000000;     // Columnas
    PORTB= 0;              // Reset filas
    PORTD= 0;              // Reset columnas
    
    while (1){
        for(unsigned char i = 0; i < 6; i++){
            
            for(t = 0; t < 40; t++){ 
                
                for(unsigned char j = 0; j < 8; j++){                                   
                    PORTB = (unsigned char)(1 << j); 
                    
                    // CORRECCIÓN: Invertimos los bits antes de aplicar la negación (~)
                    PORTD = ~invertirByte(patrones[i][j]); 
                    
                    __delay_ms(4); // Tiempo que se queda encendida cada fila
                }
            }
        }
    }
}