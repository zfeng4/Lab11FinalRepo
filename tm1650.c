/*
 * File:   tm1650.c
 * Author: Dennis
 *
 * Created on March 26, 2019, 4:14 PM
 */

#include "tm1650.h"

bool displayState;

static void writeData(uint8_t address, uint8_t data){
    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;
    uint8_t dataToSend = data;
    I2C1_MasterWrite(&dataToSend, 1, address, &status);
    while( status == I2C1_MESSAGE_PENDING ); // wait for transaction to complete
}

void TM1650_init(){
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    TM1650_enable(1);
    
    
}

void TM1650_setDigit(uint8_t digit, char num, bool dp){
    const uint8_t charTable[] = {
        0x00, 0x82, 0x21, 0x00, 0x00, 0x00, 0x00, 0x02, 0x39, 0x0F, 0x00, 0x00, 0x00, 0x40, 0x80, 0x00,
        0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7f, 0x6f, 0x00, 0x00, 0x00, 0x48, 0x00, 0x53,
        0x00, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x6F, 0x76, 0x06, 0x1E, 0x00, 0x38, 0x00, 0x54, 0x3F,
        0x73, 0x67, 0x50, 0x6D, 0x78, 0x3E, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x39, 0x00, 0x0F, 0x00, 0x08, 
        0x63, 0x5F, 0x7C, 0x58, 0x5E, 0x7B, 0x71, 0x6F, 0x74, 0x02, 0x1E, 0x00, 0x06, 0x00, 0x54, 0x5C,
        0x73, 0x67, 0x50, 0x6D, 0x78, 0x1C, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x39, 0x30, 0x0F, 0x00, 0x00 
    };
    
    uint8_t character = charTable[num - 32];
    
    if(dp){
        character = 0b10000000 | character;
    }
    
    writeData(0x34 + digit, character);

}

void putch(char putChar){
    if(putChar == 13){
        writeData(0x34, 0b00000000);
        writeData(0x35, 0b00000000);
        writeData(0x36, 0b00000000);
        writeData(0x37, 0b00000000);
        counter = 0;
    } else {
        TM1650_setDigit(counter, putChar, 0);
        counter++;
    }
    
}

void TM1650_fastPrintNum(uint16_t inputNumber){
    //char characterStorageArray[4];
    
    if(0 <= inputNumber && inputNumber <= 9){
        //characterStorageArray[0] = inputNumber + '0';
        TM1650_setDigit(0, ' ', 0);
        TM1650_setDigit(1, ' ', 0);
        TM1650_setDigit(2, ' ', 0);
        TM1650_setDigit(3, inputNumber + 48, 0);
    } else if (10 <= inputNumber && inputNumber <= 99) {
        TM1650_setDigit(0, ' ', 0);
        TM1650_setDigit(1, ' ', 0);
        TM1650_setDigit(2, ((inputNumber / 10) % 10) + 48, 0);
        TM1650_setDigit(3, (inputNumber % 10) + 48, 0);
    } else if (100 <= inputNumber && inputNumber <= 999){
        TM1650_setDigit(0, ' ', 0);
        TM1650_setDigit(1, ((inputNumber / 100) % 10) + 48, 0);
        TM1650_setDigit(2, ((inputNumber / 10) % 10) + 48, 0);
        TM1650_setDigit(3, (inputNumber % 10) + 48, 0);
    } else if (1000 <= inputNumber && inputNumber <= 9999){
        TM1650_setDigit(0, ((inputNumber / 1000) % 10) + 48, 0);
        TM1650_setDigit(1, ((inputNumber / 100) % 10) + 48, 0);
        TM1650_setDigit(2, ((inputNumber / 10) % 10) + 48, 0);
        TM1650_setDigit(3, (inputNumber % 10) + 48, 0);
    } else {
        TM1650_setDigit(0, 'E', 0);
        TM1650_setDigit(1, 'r', 0);
        TM1650_setDigit(2, 'r', 0);
        TM1650_setDigit(3, ' ', 0);
    }
    __delay_ms(10);
    
}

void TM1650_enable(bool enable){
    if(enable){
        writeData(0x24, 0x01); 
        displayState = true;
    } else if(!enable){
        writeData(0x24, 0x00);
        displayState = false;
    }
   
}

bool TM1650_isEnabled(){
    return displayState;
}