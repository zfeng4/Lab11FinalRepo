/* 
 * File:   lights.h
 * Author: Dennis
 *
 * Created on April 17, 2019, 5:31 PM
 */

#ifndef LIGHTS_H
#define	LIGHTS_H

#include <xc.h>
#include <stdint.h>
#include "clock.h"
#define _XTAL_FREQ 4000000
#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)
#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)
#pragma config WDTE = OFF

void LED_init();
void LED_setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
void UART_init();
void DMX_init();
void handler();
//void __interrupt() lightInterrupt();

int pointer;
extern uint8_t inputArray[513];
extern time_t lastActiveDMXTime;

#endif	/* LIGHTS_H */

