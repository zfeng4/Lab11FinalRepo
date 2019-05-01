/* 
 * File:   controller.h
 * Author: Dennis
 *
 * Created on April 14, 2019, 6:28 PM
 */

#ifndef CONTROLLER_H
#define	CONTROLLER_H

#include "buttons.h"
#include "clock.h"
#include "tm1650.h"

uint16_t address = 1;

void CONTROLLER_init();
void address_inc();
void address_dec();
void CONTROLLER_task();
time_t lastActiveTime;


#endif	/* CONTROLLER_H */

