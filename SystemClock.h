/*
 * SystemClock.h
 *
 *  Created on: Apr 14, 2024
 *      Author: Richard Harrison
 */

#ifndef SYSTEMCLOCK_H_
#define SYSTEMCLOCK_H_

#include <HAL/Timer.h>


struct _SystemClock{
    SWTimer timer;
    uint64_t elaspedTime;
    double deltaTime;
};
typedef struct _SystemClock SystemClock;


SystemClock SystemClock_construct();

void SystemClock_UpdateClock(SystemClock* clk);


#endif /* SYSTEMCLOCK_H_ */
