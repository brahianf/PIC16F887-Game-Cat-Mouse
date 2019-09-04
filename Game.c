// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF            // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF           // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON            // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF              // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF             // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF           // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF            // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF           // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF             // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V       // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF            // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic16f887.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"


#define _XTAL_FREQ 4000000

void main(void) {
    
    unsigned char iconVidas[8];                          //
    unsigned char iconAtrapado[3];                       // numero de saltos rato
    
    unsigned char imagenGato[3];  
    unsigned char imagenRaton[3];
    unsigned char blanco[3];
     
   
    int jumpRat=0;                                   // variable para el contador de saltos raton
    int vidasGat=7;
    int atrapado=0;
    
    int AuxPosAnteriorRat;
    int AuxPosAnteriorGat;
    
    unsigned int var=2000;                       //variable Auxiliar para TMR1
    
    int posRat;                         // varible para almacenar posicion del Ratón
    int posGat=rand()%(10)+4;            // valor Aleatorio de la posicion del gato  //rand() % ((nº mas alto - nº mas bajo +1) + nº más bajo)
    AuxPosAnteriorGat=posGat;
    //posGat=posLCD[posGat];              // posicion inicial gato en un Led
   
    
    ANSEL=0;                            // seleccionamos los puertos como digitales
    ANSELH=0;
    
    TRISB=0x00;                         // Salida LCD
    
    TRISE=0b00000011;                   // RE0, RE1 Entrada pulsadores de movimiento gato, RA7 Led para indicador gato atrapa raton

    T1CON=0b00110001;                   // TMR1 como temporizador con preescaler de 8, Activar TMR1
    INTCON=0b11000000;                  // Interrupciónes habilitadas (bits GIE y PEIE)
    
    PIE1bits.TMR1IE=1;                   // Interrupcion habilitada por desbordamiento        
    PIR1bits.TMR1IF=0;                   // Poner a 0 bandera de desbordamiento TMR1IF
    
    TMR1=2000;                          // inicializar TMR1   retardo= (1*10^-6)(65535-6000)*8=  476 ms
    
    Lcd_Init();                         //inicializamos el lcd
    Lcd_Cmd(LCD_CLEAR);                 //limpiamos lcd
    Lcd_Cmd(LCD_CURSOR_OFF);            //apagamos el cursor
    __delay_ms(100);                    //esperamos 100ms
    
    sprintf(iconVidas,"Vid%02d",vidasGat);   //guardamos en el string VidasGat el numero de vidas del Gato inicializado en 7
    Lcd_Out2(2,10,iconVidas);             //escribimos en 2 fila, 5 Columna las vidas del gato;
    
    sprintf(iconAtrapado,"At%02d",atrapado); //guardamos en el string VidasGat el numero de vidas del Gato inicializado en 7
    Lcd_Out2(2,0,iconAtrapado);             //escribimos en 2 fila, 5 Columna las vidas del gato;
    
    sprintf(imagenGato,"G","");
    Lcd_Out2(1,posGat,imagenGato);  
    
    
}