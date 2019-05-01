/*
 * File:   buttons.c
 * Author: Dennis
 *
 * Created on April 14, 2019, 6:26 PM
 */


#include <xc.h>
#include <stdbool.h>
#include "buttons.h"
#include "clock.h"

static time_t lastTime;


void BUTTONS_task(){
    time_t time = CLOCK_getTime();

    // only run every 10 ms
    if (time - lastTime < BUTTON_SCAN_INTERVAL)
        return;

    lastTime = time;

    // walk through the list of buttons and update everything
    for (uint8_t i = 0; i < BUTTON_COUNT; i++) {
        button_t* btn = buttons + i;
        
        // figure out if the button is currently activated or not
        if ((*(btn->port) & (1 << (btn->pin))) == 0) {
            btn->state = STATE_PRESSED;
        } else {
            btn->state = STATE_UNPRESSED;
        }
        
        if(btn->state == STATE_PRESSED && btn->lastState == STATE_UNPRESSED){
            btn->timeHeld = time;
        }
        
        if (
            btn->state == STATE_UNPRESSED
            && btn->lastState == STATE_PRESSED
            && (time - btn->timeHeld) <= HOLD_TIME) {
            // we released the button
            btn->event = EVENT_PRESSED;
            
        } 
        if (btn->state == STATE_UNPRESSED
            && btn->lastState == STATE_PRESSED
            && (time - btn->timeHeld) > HOLD_TIME) {
            
            btn->event = EVENT_IDLE;
            
        } if (btn->state == STATE_PRESSED && (time - btn->timeHeld) > HOLD_TIME) {
            btn -> event = EVENT_HELD;
        }

        btn->lastState = btn->state;
    }
}

static void init(button_t* btn, volatile uint8_t* port, uint8_t pin) {
    btn->port = port;
    btn->pin = pin;
    btn->state = STATE_UNPRESSED;
    btn->event = EVENT_IDLE;
}

void BUTTONS_init() {
    menu = &buttons[0];
    up = &buttons[1];
    down = &buttons[2];
    enter = &buttons[3];

    init(menu, &PORTC, 2);
    init(enter, &PORTA, 2);
    init(down, &PORTC, 0);
    init(up, &PORTC, 1);
}

bool BUTTONS_isClicked(button_t* button) {
    if (button->event == EVENT_PRESSED) {
        button->event = EVENT_IDLE;
        return true;
        
    }
    
    return false;
}

bool BUTTONS_isHeld(button_t* button) {
    if (button->event == EVENT_HELD) {
        return true;
    }
    return false;
}