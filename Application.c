/*
 * Application.c
 *
 *  Created on: Apr 11, 2024
 *      Author: Richard Harrison
 */

#include <Application.h>

#define TITLE_SCREEN_MAX_TIME 5.0


extern const Graphics_Image GALAXY_IMAGE_008BPP_UNCOMP;


//===BASE APPLICATION FUNCTIONS===//
Application Application_construct() {
    Application app;

    // UART ATTRIBUTES
    app.firstCall = true;
    app.baudChoice = BAUD_9600;

    // FINITIE STATE MACHINE
    app.appFSMstate = TITLE_SCREEN;
    app.mainMenuCursor1 = PLAYGAME;
    app.mainMenuCursor2 = SPACEINVADERS;

    // APPLICATION TIME ATTRIBUTES
    app.timer_titleScreenTime = 0.0;

    // STATE REFRESH ATTRIBUTES
    app.refreshTitleScreen = true;
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
void Application_ScreenFSM(Application* app_p, HAL* hal_p, SystemClock* clk_p) {
    switch (app_p->appFSMstate) {
    case TITLE_SCREEN:
        Application_RenderTitleScreen(app_p, hal_p, clk_p);
        Application_UpdateTitleScreen(app_p, hal_p, clk_p);
        break;
    case MAIN_MENU_SCREEN:
        Application_RenderMainScreen(app_p, hal_p, clk_p);
        Application_UpdateMainScreen(app_p, hal_p, clk_p);
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
void Application_loop(Application* app_p, HAL* hal_p, SystemClock* clk_p) {
    if (Button_isTapped(&hal_p->boosterpackS2) || app_p->firstCall) {
      Application_updateCommunications(app_p, hal_p);
    }

    Application_ScreenFSM(app_p, hal_p, clk_p);
}


//===STATE FUNCTIONS===//
void Application_UpdateTitleScreen(Application* app_p, HAL* hal_p, SystemClock* clk_p) {
    app_p->timer_titleScreenTime += clk_p->deltaTime;

    //APPLICATION_MAX_TITLE_SCREEN_TIME
    if (app_p->timer_titleScreenTime >  TITLE_SCREEN_MAX_TIME) {
        app_p->appFSMstate = MAIN_MENU_SCREEN;
        app_p->refreshMainMenuScreen = true;
        GFX_clear(&hal_p->gfx);
    }
}

void Application_RenderTitleScreen(Application* app_p, HAL* hal_p, SystemClock* clk_p) {
    if (app_p->refreshTitleScreen) {
        Graphics_drawImage(&hal_p->gfx.context, &GALAXY_IMAGE_008BPP_UNCOMP, 0, 0);
        app_p->refreshTitleScreen = false;
    }
}

/**
 * [Description Here]
 *
 * @param app_p:  A pointer to the main Application object.
 * @param hal_p:  A pointer to the main HAL object
 */
void Application_UpdateMainScreen(Application* app_p, HAL* hal_p, SystemClock* clk_p) {
    if (Joystick_isTappedUp(&hal_p->joystick)) {
        uint32_t newCursorPosition = Helper_CircularDecrement((uint32_t)app_p->mainMenuCursor1, NUM_CURSOR_STATES_1);
        app_p->mainMenuCursor1 = (MainMenuCursor1)newCursorPosition;
    }
    else if (Joystick_isTappedDown(&hal_p->joystick)) {
        uint32_t newCursorPosition = Helper_CircularIncrement((uint32_t)app_p->mainMenuCursor1, NUM_CURSOR_STATES_1);
        app_p->mainMenuCursor1 = (MainMenuCursor1)newCursorPosition;
    }

    if (Button_isTapped(&hal_p->boosterpackJS)) {
        GFX_clear(&hal_p->gfx);
        switch (app_p->mainMenuCursor1) {
        case PLAYGAME:
            switch(app_p->mainMenuCursor2) {
            case SPACEINVADERS:
                app_p->appFSMstate = GAME_SCREEN_SPACE_INVADERS;
                break;
            }
            //app_p->refreshGameScreen = true;
            break;
        case VIEWINSTRUCTIONS:
            switch(app_p->mainMenuCursor2) {
            case SPACEINVADERS:
                app_p->appFSMstate = INSTRUCTIONS_SCREEN_SPACE_INVADERS;
                break;
            }
           // app_p->refreshInstructionScreen = true;
            break;
        case VIEWHIGHSCORE:
            switch(app_p->mainMenuCursor2) {
            case SPACEINVADERS:
                app_p->appFSMstate = HIGH_SCORE_SCREEN_SPACE_INVADERS;
                break;
            }
            //app_p->refreshHighScoreScreen = true;
            break;
        default:
            break;
        }
    }
}


/**
 * [Description Here]
 *
 * @param app_p:  A pointer to the main Application object.
 * @param hal_p:  A pointer to the main HAL object
 */
void Application_RenderMainScreen(Application* app_p, HAL* hal_p, SystemClock* clk_p) {
    static MainMenuCursor1 currentCursor1 = PLAYGAME;
    static MainMenuCursor2 currentCursor2 = SPACEINVADERS;

    if (currentCursor1 != app_p->mainMenuCursor1 || app_p->refreshMainMenuScreen) {
        currentCursor1 = app_p->mainMenuCursor1;

        GFX_print(&hal_p->gfx, " ", 6, 2);
        GFX_print(&hal_p->gfx, " ", 7, 2);
        GFX_print(&hal_p->gfx, " ", 8, 2);

        switch (currentCursor1) {
        case PLAYGAME:
            GFX_print(&hal_p->gfx, ">", 6, 2);
            break;
        case VIEWINSTRUCTIONS:
            GFX_print(&hal_p->gfx, ">", 7, 2);
            break;
        case VIEWHIGHSCORE:
            GFX_print(&hal_p->gfx, ">", 8, 2);
            break;
        default:
            break;
        }
    }

    if (currentCursor2 != app_p->mainMenuCursor2 || app_p->refreshMainMenuScreen) {
        currentCursor2 = app_p->mainMenuCursor2;

        GFX_print(&hal_p->gfx, "                                   ", 12, 0);

        switch(app_p->mainMenuCursor2) {
        case SPACEINVADERS:
            GFX_print(&hal_p->gfx, "Space Invaders", 12, 4);
            break;
        default:
            break;
        }
    }



    if (app_p->refreshMainMenuScreen) {
        GFX_print(&hal_p->gfx, "Play ECE Surfers", 6, 3);
        GFX_print(&hal_p->gfx, "Instructions"    , 7, 3);
        GFX_print(&hal_p->gfx, "View High Scores", 8, 3);

        GFX_print(&hal_p->gfx, "< O >", 11, 9);
        app_p->refreshMainMenuScreen = false;
    }
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

uint32_t Helper_CircularIncrement(uint32_t value, uint32_t maximum) {
    return (value + 1) % maximum;
}

uint32_t Helper_CircularDecrement(uint32_t value, uint32_t maximum) {
    if (value == 0)
        return maximum - 1;
    return (value - 1) % maximum;
}
