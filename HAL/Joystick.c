/*
 * Joystick.c
 *
 *  Created on: Mar 28, 2024
 *      Author: Richard Harrisons
 */

#include <HAL/Joystick.h>


#define LEFT_THRESHOLD 3000
#define RIGHT_THRESHOLD 12000
#define UP_THRESHOLD 12000
#define DOWN_THRESHOLD 3000


enum _JoystickDebounceStateLeft { NOT_LEFT, LEFT};
typedef enum _JoystickDebounceStateLeft JoystickDebounceStateLeft;

enum _JoystickDebounceStateRight { NOT_RIGHT, RIGHT};
typedef enum _JoystickDebounceStateRight JoystickDebounceStateRight;

enum _JoystickDebounceStateUp {NOT_UP, UP};
typedef enum _JoystickDebounceStateUp JoystickDebounceStateUp;

enum _JoystickDebounceStateDown {NOT_DOWN, DOWN};
typedef enum _JoystickDebounceStateDown JoystickDebounceStateDown;


void initADC() {
    ADC14_enableModule();

    ADC14_initModule(ADC_CLOCKSOURCE_SYSOSC, ADC_PREDIVIDER_1, ADC_DIVIDER_1, 0);

    // This configures the ADC to store output results in ADC_MEM0 for joystick X.
    ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, true);

    // This configures the ADC in manual conversion mode Software will start each conversion.
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
}

void initJoyStick() {

    // This configures ADC_MEM0 to store the result from
    // input channel A15 (Joystick X), in non-differential input mode
    // (non-differential means: only a single input pin)
    // The reference for Vref- and Vref+ are VSS and VCC respectively
    ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A15, ADC_NONDIFFERENTIAL_INPUTS);

    // This selects the GPIO as analog input
    // A15 is multiplexed on GPIO port P6 pin PIN0
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);

    // Initialization for Y
    ADC14_configureConversionMemory(ADC_MEM1, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A9, ADC_NONDIFFERENTIAL_INPUTS);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);
}

void startADC() {
   // Starts the ADC with the first conversion
   // in repeat-mode, subsequent conversions run automatically
   ADC14_enableConversion();
   ADC14_toggleConversionTrigger();
}

Joystick Joystick_construct() {
    Joystick joystick;

    initADC();
    initJoyStick();
    startADC();

    joystick.isTappedToLeft = false;
    joystick.isTappedToRight = false;
    joystick.isTappedUp = false;
    joystick.isTappedDown = false;

    return joystick;
}

bool Joystick_isPressedToLeft(Joystick* joystick_p) {
    return (joystick_p->x < LEFT_THRESHOLD);
}

bool Joystick_isPressedToRight(Joystick* joystick_p) {
    return (joystick_p->x > RIGHT_THRESHOLD);
}

bool Joystick_isPressedUp(Joystick* joystick_p) {
    return (joystick_p->y > UP_THRESHOLD);
}

bool Joystick_isPressedDown(Joystick* joystick_p) {
    return (joystick_p->y < DOWN_THRESHOLD);
}

bool Joystick_isTappedToLeft(Joystick* joystick_p) {
    return joystick_p->isTappedToLeft;
}

bool Joystick_isTappedToRight(Joystick* joystick_p) {
    return joystick_p->isTappedToRight;
}

bool Joystick_isTappedUp(Joystick* joystick_p) {
    return joystick_p->isTappedUp;
}

bool Joystick_isTappedDown(Joystick* joystick_p) {
    return joystick_p->isTappedDown;
}

void Joystick_refresh(Joystick* joystick_p) {
    Joystick_refresh_X(joystick_p);
    Joystick_refresh_Y(joystick_p);
}

void Joystick_refresh_X(Joystick* joystick_p) {
    static JoystickDebounceStateLeft leftState = NOT_LEFT;
    static JoystickDebounceStateRight rightState = NOT_RIGHT;

    joystick_p->x = ADC14_getResult(ADC_MEM0);

    joystick_p->isTappedToLeft = false;
    joystick_p->isTappedToRight = false;

    switch (leftState) {
    case NOT_LEFT:
        if (joystick_p->x < LEFT_THRESHOLD) {
            leftState = LEFT;
            rightState = NOT_RIGHT;
            joystick_p->isTappedToLeft = true;
        }
        break;
    case LEFT:
        if (joystick_p->x > LEFT_THRESHOLD) {
            leftState = NOT_LEFT;
        }
        break;
    }

    switch (rightState) {
    case NOT_RIGHT:
        if (joystick_p->x > RIGHT_THRESHOLD) {
            rightState = RIGHT;
            leftState = NOT_LEFT;
            joystick_p->isTappedToRight = true;
        }
        break;
    case RIGHT:
        if (joystick_p->x < RIGHT_THRESHOLD) {
            rightState = NOT_RIGHT;
        }
        break;
    }
}

void Joystick_refresh_Y(Joystick* joystick_p) {
    static JoystickDebounceStateUp upState = NOT_UP;
    static JoystickDebounceStateDown downState = NOT_DOWN;

    joystick_p->y = ADC14_getResult(ADC_MEM1);

    joystick_p->isTappedUp = false;
    joystick_p->isTappedDown = false;

    switch (upState) {
    case NOT_UP:
        if (joystick_p->y > UP_THRESHOLD) {
            upState = UP;
            downState = NOT_DOWN;
            joystick_p->isTappedUp = true;
        }
        break;
    case UP:
        if (joystick_p->y < UP_THRESHOLD) {
            upState = NOT_UP;
        }
        break;
    }

    switch (downState) {
    case NOT_DOWN:
        if (joystick_p->y < DOWN_THRESHOLD) {
            downState = DOWN;
            upState = NOT_UP;
            joystick_p->isTappedDown = true;
        }
        break;
    case DOWN:
        if (joystick_p->y > DOWN_THRESHOLD) {
            downState = NOT_DOWN;
        }
        break;
    }
}
