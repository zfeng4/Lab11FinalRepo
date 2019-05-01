/*
 * File:   lights.c
 * Author: Dennis
 *
 * Created on April 17, 2019, 5:31 PM
 */

#include "lights.h"
#include "mcc_generated_files/eusart1.h"


//this function routes the decoded UART number to the LED_setColor function
uint8_t inputArray[513];
time_t lastActiveDMXTime;

int point;

void handler() {
    LATC5 = 1;
    if(RC1STAbits.OERR == 1){
                RC1STAbits.CREN = 0;
                RC1STAbits.CREN = 1;
            }
            uint8_t dataIn = RC1REG;
            if(RC1STAbits.FERR == 1){
                point = 0;
            }else if(point > 513){
                //OOF
            }else{
                inputArray[point] = dataIn;
                point++;
            }
    LATC5 = 0;
}

void DMX_init() {
    EUSART1_SetRxInterruptHandler(handler);
    TRISB4 = 1;
    ANSELB = 0x00;
    //*point = 0;
    point = 0;
}

void LED_init(){
    //step 1
    RC7PPS = 0x09; //CCP1OUT Red
    //PMD4bits.CCP1MD = 0;
    RC6PPS = 0x0A; //CCP2OUT Green
    //PMD4bits.CCP2MD = 0;
    RC3PPS = 0x0B; //CCP3OUT Blue
    //PMD4bits.CCP3MD = 0;
    RC4PPS = 0x0C; //CCP4OUT White
        
    //step 2
    //T2CONbits.CKPS = 0b101; //pre-scalar
        
    //step 3
    CCP1CONbits.MODE = 0b1100;
    CCP1CONbits.CCP1EN = 1;
        
    CCP2CONbits.MODE = 0b1100;
    CCP2CONbits.CCP2EN = 1;
    
    CCP3CONbits.MODE = 0b1100;
    CCP3CONbits.CCP3EN = 1;
        
    CCP4CONbits.MODE = 0b1100;
    CCP4CONbits.CCP4EN = 1;
        
        
    T2CLKCON = 0x01;
    T2CONbits.ON = 1;

    TRISC7 = 0;
    TRISC6 = 0;
    TRISC3 = 0;
    TRISC4 = 0;
        
    return;
}

void LED_setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t white){  
    if(red < 256 && green < 256 && blue < 256 && white < 256){
        red = ((float)red / 2048) * (_XTAL_FREQ / (122 * 32));
        green = ((float)green / 2048) * (_XTAL_FREQ / (122 * 32));
        blue = ((float)blue / 2048) * (_XTAL_FREQ / (122 * 32));
        white = ((float)white / 2048) * (_XTAL_FREQ / (122 * 32));
    } else {
        red = ((float)255 / 2048) * (_XTAL_FREQ / (122 * 32));
        green = ((float)255 / 2048) * (_XTAL_FREQ / (122 * 32));
        blue = ((float)255 / 2048) * (_XTAL_FREQ / (122 * 32));
        white = ((float)255 / 2048) * (_XTAL_FREQ / (122 * 32));
    }
    
    CCPR1 = red; //duty cycle
    CCPR2 = green; //duty cycle
    CCPR3 = blue; //duty cycle
    CCPR4 = white; //duty cycle
    
    return;
}

//this initializes the UART
void UART_init(){
    SP1BRG = 0x03; //maybe it doesn't need to be in hex
    
    TX1STAbits.SYNC = 0;
    TX1STAbits.BRGH = 1;
    BAUD1CONbits.BRG16 = 1;
    //BAUD1CONbits.SCKP = 0;
    
    //RB4PPS = 0x0F;
    RX1PPS = 0b00001100;
    
    RC1STAbits.SPEN = 1;
    //TX1STAbits.TXEN = 0;
    
    RC1STAbits.RX9 = 0;
    RC1STAbits.CREN = 1;
    TX1STAbits.TXEN = 0;
    
    TRISB4 = 1;
    ANSELB = 0x00;
    
    pointer = 0;
    PIE3bits.RC1IE = 1;
}
