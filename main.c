/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F18446
        Driver Version    :  2.00
//*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "tm1650.h"
#include "lights.h"
#include "buttons.h"
#include "clock.h"
#include "controller.h"
#include "beat.h"
#include <stdint.h>
#include <stdio.h>

static time_t lastTime;

/*
        Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    __delay_ms(50);
    TM1650_init();
    CLOCK_init();
    BUTTONS_init();
    CONTROLLER_init();
    DMX_init();
    LED_init();
    BEAT_init();
    
    while (1)
    {
        BUTTONS_task();
        CONTROLLER_task();
        BEAT_task();
        TM1650_fastPrintNum(address);
        
        if((CLOCK_getTime() - lastActiveDMXTime) <= 50){
            LED_setColor(inputArray[address], inputArray[address+1], inputArray[address+2], inputArray[address+3]);
        } else if ((CLOCK_getTime() - lastActiveDMXTime) > 50) {
            //beat detection
            time_t time = CLOCK_getTime();
        
            if(time - lastTime < 100){
                continue;
            }
        
            lastTime = time;
        
            if(BEAT_detected()){
                int randomNumber = rand() % 10;
                if(randomNumber == 0) {
                    //Red
                    LED_setColor(200, 0, 0, 0);
                } else if (randomNumber == 1) {
                    //Orange
                    LED_setColor(200, 200, 0, 0);
                } else if (randomNumber == 2) {
                    //Yellow
                    LED_setColor(70, 200, 0, 0);
                } else if (randomNumber == 3) {
                    //Green
                    LED_setColor(0, 200, 0, 0);
                } else if (randomNumber == 4) {
                    //Turquoise
                    LED_setColor(0, 200, 200, 0);
                } else if (randomNumber == 5) {
                    //Blue
                    LED_setColor(0, 0, 200, 0);
                } else if (randomNumber == 6) {
                    //Purple
                    LED_setColor(14, 0, 200, 0);
                } else if (randomNumber == 7) {
                    //Magenta
                    LED_setColor(200, 0, 200, 0);
                } else if (randomNumber == 8) {
                    //White
                    LED_setColor(0, 0, 0, 250);
                }
            } else {
                
            }
        }
    }
}
/**
 End of File
*/
