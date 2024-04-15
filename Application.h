/*
 * Application.h
 *
 *  Created on: Apr 11, 2024
 *      Author: Richard Harrison
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <HAL/HAL.h>
#include <SystemClock.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


enum _APPLICATION_FSM_STATES {
    TITLE_SCREEN,
    MAIN_MENU_SCREEN,
    INSTRUCTIONS_SCREEN,
    INSTRUCTIONS_SCREEN_SPACE_INVADERS,
    GAME_SCREEN,
    GAME_SCREEN_SPACE_INVADERS,
    GAME_OVER_SCREEN,
    HIGH_SCREEN,
    HIGH_SCORE_SCREEN_SPACE_INVADERS,
    NUM_SCREENS
};
typedef enum _APPLICATION_FSM_STATES ApplicationFSMstates;

enum _MAIN_MENU_CURSOR_1 {
    PLAYGAME,
    VIEWINSTRUCTIONS,
    VIEWHIGHSCORE,
    NUM_CURSOR_STATES_1
};
typedef enum _MAIN_MENU_CURSOR_1 MainMenuCursor1;

enum _MAIN_MENU_CURSOR_2 {
    SPACEINVADERS,
    NUM_CURSOR_STATES_2
};
typedef enum _MAIN_MENU_CURSOR_2 MainMenuCursor2;


struct _Application {
    // UART ATTRIBUTES
    bool firstCall;
    UART_Baudrate baudChoice;

    // FINITIE STATE MACHINE
    ApplicationFSMstates appFSMstate;
    MainMenuCursor1 mainMenuCursor1;
    MainMenuCursor2 mainMenuCursor2;

    // TIMER ATTRIBUTES
    double timer_titleScreenTime;

    // STATE REFRESH ATTRIBUTES
    bool refreshTitleScreen;
    bool refreshMainMenuScreen;


};
typedef struct _Application Application;


//===BASE APPLICATION FUNCTIONS===//
// Called only a single time - inside of main(), where the application is constructed
Application Application_construct();

// Called whenever the UART module needs to be updated
void Application_updateCommunications(Application* app_p, HAL* hal_p);

// Called once per sub-loop of the application loop
void Application_ScreenFSM(Application* app_p, HAL* hal_p, SystemClock* clk_p);

// Called once per super-loop of the main application.
void Application_loop(Application* app_p, HAL* hal_p, SystemClock* clk_p);


//===STATE FUNCTIONS===//
// Updates the Title Screen
void Application_UpdateTitleScreen(Application* app_p, HAL* hal_p, SystemClock* clk_p);

// Renders the Title Screen
void Application_RenderTitleScreen(Application* app_p, HAL* hal_p, SystemClock* clk_p);

// Updates the Main Screen
void Application_UpdateMainScreen(Application* app_p, HAL* hal_p, SystemClock* clk_p);

// Renders the Main Screen
void Application_RenderMainScreen(Application* app_p, HAL* hal_p, SystemClock* clk_p);

// Updates the Instruction Screen
void Application_UpdateInstructionScreen(Application* app_p, HAL* hal_p, double deltaTime);

// Renders the Instruction Screen
void Application_RenderInstructionScreen(Application* app_p, HAL* hal_p, double deltaTime);

// Updates the Game Screen
void Application_UpdateGameScreen(Application* app_p, HAL* hal_p, double deltaTime);

// Renders the Game Screen
void Application_RenderGameScreen(Application* app_p, HAL* hal_p, double deltaTime);

// Updates the Game Over Screen
void Application_UpdateGameOverScreen(Application* app_p, HAL* hal_p, double deltaTime);

// Renders the Game Over Screen
void Application_RenderGameOverScreen(Application* app_p, HAL* hal_p, double deltaTime);

// Updates the HighScore Screen
void Application_UpdateHighScoreScreen(Application* app_p, HAL* hal_p, double deltaTime);

// Renders the HighScore Screen
void Application_RenderHighScoreScreen(Application* app_p, HAL* hal_p, double deltaTime);


//===HELPER FUNCTIONS===//
// Prints the given string to the UART screen
void Helper_printToUART(HAL* hal_p, char* string, bool newLine);

// Circularly increments
uint32_t Helper_CircularIncrement(uint32_t value, uint32_t maximum);

// Circularly decrements
uint32_t Helper_CircularDecrement(uint32_t value, uint32_t maximum);


#endif /* APPLICATION_H_ */
