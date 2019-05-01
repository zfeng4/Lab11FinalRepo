/* 
 * File:   lab11Header.h
 * Author: Dennis
 *
 * Created on April 14, 2019, 4:55 PM
 */

#ifndef CLOCK_H
#define	CLOCK_H

#include <stdint.h>
    
typedef uint16_t time_t;

void CLOCK_init();
time_t CLOCK_getTime();




#endif	/* CLOCK_H */