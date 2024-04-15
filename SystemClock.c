/*
 * SystemClock.c
 *
 *  Created on: Apr 14, 2024
 *      Author: Richard Harrison
 */


#include <SystemClock.h>


SystemClock SystemClock_construct() {
    SystemClock clk;

    clk.elaspedTime = 0;
    clk.deltaTime = 0.0;

    SWTimer_start(&clk.timer);
    SWTimer_elapsedTimeUS(&clk.timer);

    return clk;
}

void SystemClock_UpdateClock(SystemClock* clk) {
    uint64_t full = SWTimer_elapsedTimeUS(&clk->timer);

    clk->deltaTime = (full - clk->elaspedTime) / 1000000.0;

    clk->elaspedTime = full;
}
