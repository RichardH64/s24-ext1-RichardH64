/*
 * Application.c
 *
 *  Created on: Apr 11, 2024
 *      Author: Richard Harrison
 */

#include <Application.h>
#include <Images/Animation/GalaxyAnimation.h>

//===BASE APPLICATION FUNCTIONS===//
void Application_construct() {
    Application app;

    // UART ATTRIBUTES
    app.firstCall = true;
    app.baudChoice = BAUD_9600;

    // FINITIE STATE MACHINE
    app.appFSMstate = TITLE_SCREEN;

    // APPLICATION TIME ATTRIBUTES
    app.TimeSinceLastCall = 0;

    app.titleScreenTime = 0;

    // STATE REFRESH ATTRIBUTES
    app.refreshMainMenuScreen = true;

    return app;
}

/**
 * Updates which LEDs are lit and what baud rate the UART module communicates
 * with, based on what the application's baud choice is at the time this
 * function is called.
 *
 * @param app_p:  A pointer to the main Application object.
 * @param hal_p:  A pointer to the main HAL object
 */
void Application_updateCommunications(Application* app_p, HAL* hal_p) {
    // When this application first loops, the proper LEDs aren't lit. The
    // firstCall flag is used to ensure that the
    if (app_p->firstCall) {
      app_p->firstCall = false;
    }

    // When BoosterPack S2 is tapped, circularly increment which baud rate is
    // used.
    else {
      uint32_t newBaudNumber =
              Helper_CircularIncrement((uint32_t)app_p->baudChoice, NUM_BAUD_CHOICES);
      app_p->baudChoice = (UART_Baudrate)newBaudNumber;
    }

    // Start/update the baud rate according to the one set above.
    UART_SetBaud_Enable(&hal_p->uart, app_p->baudChoice);

    // Based on the new application choice, turn on the correct LED.
    // To make your life easier, we recommend turning off all LEDs before
    // selectively turning back on only the LEDs that need to be relit.
    // -------------------------------------------------------------------------
    LED_turnOff(&hal_p->launchpadLED2Red);
    LED_turnOff(&hal_p->launchpadLED2Green);
    LED_turnOff(&hal_p->launchpadLED2Blue);

    // Turn on all appropriate LEDs according to the tasks below.
    switch (app_p->baudChoice) {
      // When the baud rate is 9600, turn on Launchpad LED Red
      case BAUD_9600:
        LED_turnOn(&hal_p->launchpadLED2Red);
        break;

      // When the baud rate is 19200, turn on Launchpad LED Green
      case BAUD_19200:
          LED_turnOn(&hal_p->launchpadLED2Green);
        break;

      // When the baud rate is 38400, turn on Launchpad LED Blue
      case BAUD_38400:
          LED_turnOn(&hal_p->launchpadLED2Blue);
        break;

      // When the baud rate is 57600, turn on all Launchpad LEDs (illuminates white)
      case BAUD_57600:
          LED_turnOn(&hal_p->launchpadLED2Red);
          LED_turnOn(&hal_p->launchpadLED2Green);
          LED_turnOn(&hal_p->launchpadLED2Blue);
        break;

      // In the default case, this program will do nothing.
      default:
        break;
    }
}

/**
 * Finite State Machine Function for the application screens. Most of the game is handled
 * by functions within this functions.
 *
 * @param app_p:        A pointer to the main Application object.
 * @param hal_p:        A pointer to the main HAL object.
 * @param deltaTime:    A variable holding the change in time since the last update.
 */
void Application_ScreenFSM(Application* app_p, HAL* hal_p, double deltaTime) {
    switch (app_p->appFSMstate) {
    case TITLE_SCREEN:
        //Application_RenderTitleScreen(app_p, hal_p, deltaTime);
        //Application_UpdateTitleScreen(app_p, hal_p, deltaTime);
        break;
    case MAIN_MENU_SCREEN:
        //Application_RenderMainScreen(app_p, hal_p, deltaTime);
        //Application_UpdateMainScreen(app_p, hal_p, deltaTime);
        break;
    case INSTRUCTIONS_SCREEN:
        //Application_RenderInstructionScreen(app_p, hal_p, deltaTime);
        //Application_UpdateInstructionScreen(app_p, hal_p, deltaTime);
        break;
    case GAME_SCREEN:
        //Application_RenderGameScreen(app_p, hal_p, deltaTime);
        //Application_UpdateGameScreen(app_p, hal_p, deltaTime);
        break;
    case GAME_OVER_SCREEN:
        //Application_RenderGameOverScreen(app_p, hal_p, deltaTime);
        //Application_UpdateGameOverScreen(app_p, hal_p, deltaTime);
        break;
    case HIGH_SCREEN:
        //Application_RenderHighScoreScreen(app_p, hal_p, deltaTime);
        //Application_UpdateHighScoreScreen(app_p, hal_p, deltaTime);
        break;
    default:
        break;
    }
}

/**
 * The main super-loop function of the application. We place this inside of a
 * single infinite loop in main. In this way, we can model a polling system of
 * FSMs. Every cycle of this loop function, we poll each of the FSMs one time,
 * followed by refreshing all inputs to the system through a convenient
 * [HAL_refresh()] call.
 *
 * @param app_p:  A pointer to the main Application object.
 * @param hal_p:  A pointer to the main HAL object.
 */
void Application_loop(Application* app_p, HAL* hal_p) {
    if (Button_isTapped(&hal_p->boosterpackS2) || app_p->firstCall) {
      Application_updateCommunications(app_p, hal_p);
    }

    double deltaTime = Helper_GetDT();

    Application_ScreenFSM(app_p, hal_p, deltaTime);
}


//===STATE FUNCTIONS===//
void Application_UpdateTitleScreen(Application* app_p, HAL* hal_p, double deltaTime) {
    app_p->timer_titleScreenTime += deltaTime;

    //APPLICATION_MAX_TITLE_SCREEN_TIME
    if (app_p->timer_titleScreenTime >=  3) {
        app_p->appFSMstate = MAIN_MENU_SCREEN;
        app_p->refreshMainMenuScreen = true;
        GFX_clear(&hal_p->gfx);
    }
}

void Application_RenderTitleScreen(Application* app_p, HAL* hal_p, double deltaTime) {
    if (app_p->timer_titleScreenTime >= 2) {
    }
    else if (app_p->timer_titleScreenTime >= 1) {

    }
    else {

    }

    Graphics_drawImage(&hal_p->gfx.context, getGalaxyImageToRender(app_p->timer_titleScreenTime), 0, 0);

}



//===HELPER FUNCTIONS===//
void Helper_printToUART(HAL* hal_p, char* string, bool newLine) {
    int i = 0;
    while (string[i] != '\0') {
        UART_sendChar(&hal_p->uart, string[i]);
        i++;
    }
    if (newLine) {
        UART_sendChar(&hal_p->uart, '\r');
        UART_sendChar(&hal_p->uart, '\n');
    }
}

double Helper_GetDT(Application* app_p) {
    double timeSinceApplicationConstruct = SWTimer_elapsedTimeUS(&app_p->ApplicationTimer) / 1000000.0;
    double deltaTime = timeSinceApplicationConstruct - app_p->TimeSinceLastCall;
    app_p->TimeSinceLastCall = timeSinceApplicationConstruct;
    return deltaTime;
}

uint32_t Helper_CircularIncrement(uint32_t value, uint32_t maximum) {
    return (value + 1) % maximum;
}

uint32_t Helper_CircularDecrement(uint32_t value, uint32_t maximum) {
    if (value == 0)
        return maximum - 1;
    return (value - 1) % maximum;
}
