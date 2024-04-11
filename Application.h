/*
 * Application.h
 *
 *  Created on: Apr 11, 2024
 *      Author: Richard Harrison
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <HAL/HAL.h>


enum _APPLICATION_FSM_STATES {
    TITLE_SCREEN,
    MAIN_MENU_SCREEN,
    INSTRUCTIONS_SCREEN,
    GAME_SCREEN,
    GAME_OVER_SCREEN,
    HIGH_SCREEN,
    NUM_SCREENS
};
typedef enum _APPLICATION_FSM_STATES ApplicationFSMstates;

struct _Application {
    // UART ATTRIBUTES
    bool firstCall;
    UART_Baudrate baudChoice;

    // FINITIE STATE MACHINE
    ApplicationFSMstates appFSMstate;

    // APPLICATION TIME ATTRIBUTES
    double TimeSinceLastCall;
    SWTimer ApplicationTimer;

    double timer_titleScreenTime;

    // STATE REFRESH ATTRIBUTES
    bool refreshMainMenuScreen;
};
typedef struct _Application Application;


//===BASE APPLICATION FUNCTIONS===//
// Called only a single time - inside of main(), where the application is constructed
Application Application_construct();

// Called whenever the UART module needs to be updated
void Application_updateCommunications(Application* app_p, HAL* hal_p);

// Called once per sub-loop of the application loop
void Application_ScreenFSM(Application* app_p, HAL* hal_p, double deltaTime);

// Called once per super-loop of the main application.
void Application_loop(Application* app_p, HAL* hal_p);


//===STATE FUNCTIONS===//
// Updates the Title Screen
void Application_UpdateTitleScreen(Application* app_p, HAL* hal_p, double deltaTime);

// Renders the Title Screen
void Application_RenderTitleScreen(Application* app_p, HAL* hal_p, double deltaTime);

// Updates the Main Screen
void Application_UpdateMainScreen(Application* app_p, HAL* hal_p, double deltaTime);

// Renders the Main Screen
void Application_RenderMainScreen(Application* app_p, HAL* hal_p, double deltaTime);

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

// Gets the change in time since the last update
double Helper_GetDT(Application* app_p);

// Circularly increments
uint32_t Helper_CircularIncrement(uint32_t value, uint32_t maximum);

// Circularly decrements
uint32_t Helper_CircularDecrement(uint32_t value, uint32_t maximum);


#endif /* APPLICATION_H_ */
