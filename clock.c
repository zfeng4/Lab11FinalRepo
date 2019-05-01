/*
 * File:   clock.c
 * Author: Dennis
 *
 * Created on April 14, 2019, 11:26 PM
 */


#include <xc.h>
#include "clock.h"
#include "mcc_generated_files/tmr0.h"

static time_t currentTime;

static void CLOCK_timerCallback()
{
    currentTime++;
}

void CLOCK_init()
{
    TMR0_SetInterruptHandler(CLOCK_timerCallback);
}

time_t CLOCK_getTime() {
    return currentTime;
}