/*
 * File:   controller.c
 * Author: Dennis
 *
 * Created on April 14, 2019, 6:28 PM
 */

#include "controller.h"

void CONTROLLER_init() {
    TM1650_fastPrintNum(address);
}

/**
 * Increments the address and updates the display
 */
void address_inc()
{
    if(address == 512)
        address = 1;
    else
        address++;
    
    // update the display
    TM1650_fastPrintNum(address);
}

/**
 * Decrements the address and updates the display
 */
void address_dec() 
{
    if(address == 1)
        address = 512;
    else
        address--;  
    
    // update the display
    TM1650_fastPrintNum(address);
}

void CONTROLLER_task() {
    bool active = true;
    
    if (BUTTONS_isClicked(up)) {
        address_inc();
    } else if (BUTTONS_isClicked(down)) {
        address_dec();
    } else if (BUTTONS_isHeld(up)){
        address_inc();
    } else if (BUTTONS_isHeld(down)){
        address_dec();
    } else {
        active = false;
    }
    
    if(active){
        TM1650_enable(true);
        lastActiveTime = CLOCK_getTime();
    }
    
    if(CLOCK_getTime() - lastActiveTime >= 5000){
        TM1650_enable(false);
        lastActiveTime = CLOCK_getTime() - 5001;
    }
}