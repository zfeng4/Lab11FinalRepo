/* 
 * File:   beat.h
 * Author: Dennis
 *
 * Created on April 25, 2019, 9:02 PM
 */

#ifndef BEAT_H
#define	BEAT_H
#include <stdbool.h>

void BEAT_init();
void BEAT_task();
bool BEAT_detected();
static void adcThresholdHandler();

#endif	/* BEAT_H */

