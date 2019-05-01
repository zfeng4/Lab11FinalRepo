/* 
 * File:   buttons.h
 * Author: Dennis
 *
 * Created on April 14, 2019, 6:24 PM
 */
#ifndef BUTTONS_H
#define BUTTONS_H

#define BUTTON_SCAN_INTERVAL 10
#define BUTTON_COUNT 4
#define HOLD_TIME 1000
#include <stdint.h>
#include <stdbool.h>
#include "clock.h"

typedef enum {
    EVENT_IDLE,
    EVENT_PRESSED,
    EVENT_HELD
} event_t;

typedef enum {
    STATE_UNPRESSED,
    STATE_PRESSED
} btnState_t;

typedef struct {
    volatile uint8_t* port;
    uint8_t pin;
    btnState_t state;
    btnState_t lastState;
    event_t event;
    time_t timeHeld;
} button_t;

button_t buttons[BUTTON_COUNT];
button_t *up, *down, *enter, *menu;

void BUTTONS_task();
static void init(button_t* btn, volatile uint8_t* port, uint8_t pin);
void BUTTONS_init();
bool BUTTONS_isClicked(button_t* button);
bool BUTTONS_isHeld(button_t* button);

#endif