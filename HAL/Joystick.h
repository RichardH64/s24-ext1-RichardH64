/*
 * Joystick.h
 *
 *  Created on: Mar 28, 2024
 *      Author: Richard Harrison
 */

#ifndef HAL_JOYSTICK_H_
#define HAL_JOYSTICK_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void initADC();

void initJoyStick();

void startADC();

struct _Joystick {
    uint_fast16_t x;
    uint_fast16_t y;

    bool isTappedToLeft;
    bool isTappedToRight;
    bool isTappedUp;
    bool isTappedDown;
};
typedef struct _Joystick Joystick;

Joystick Joystick_construct();

bool Joystick_isPressedToLeft(Joystick* joystick_p);
bool Joystick_isPressedToRight(Joystick* joystick_p);
bool Joystick_isPressedUp(Joystick* joystick_p);
bool Joystick_isPressedDown(Joystick* joystick_p);

bool Joystick_isTappedToLeft(Joystick* joystick_p);
bool Joystick_isTappedToRight(Joystick* joystick_p);
bool Joystick_isTappedUp(Joystick* joystick_p);
bool Joystick_isTappedDown(Joystick* joystick_p);

void Joystick_refresh(Joystick* joystick_p);
void Joystick_refresh_X(Joystick* joystick_p);
void Joystick_refresh_Y(Joystick* joystick_p);
#endif /* HAL_JOYSTICK_H_ */
