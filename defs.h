#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


static SDL_Window* game_Window;
static SDL_Renderer* game_Renderer;
static SDL_Event game_event;

//Logic
bool game_Is_Running = true;

//Screen
#define SCREEN_TITLE "DiamondHead Is Running"
const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 423;
const int SCREEN_BPP = 32;

//Map
#define MAX_GROUND 380

//Player
#define CHARACTER_X_POS 120
#define CHARACTER_Y_POS 280
#define MAX_FRAME 4
#define PLAYER_SPEED 20

//TimeControl
#define ONE_SECOND 1000
#define FRAME_PER_SECOND 9

//Func
void logErrorAndExit(const std::string msg, const std::string error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, msg.c_str(), error.c_str());
    SDL_Quit();
}
void initGameWindow()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init: ", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "lineear");

    game_Window = SDL_CreateWindow(SCREEN_TITLE,
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT,
                                   SDL_WINDOW_SHOWN);

    if (game_Window == nullptr)
        logErrorAndExit("Creating Window: ", SDL_GetError());

    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
        logErrorAndExit("SDL_image error: ", SDL_GetError());

    game_Renderer = SDL_CreateRenderer(game_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (game_Renderer == nullptr)
        logErrorAndExit("Creating Renderer: ", SDL_GetError());
}
void quitGame()
{
    game_Is_Running = false;
}

void clearAll()
{
    SDL_DestroyRenderer(game_Renderer);
    game_Renderer = nullptr;

    SDL_DestroyWindow(game_Window);
    game_Window = nullptr;

    IMG_Quit();
    SDL_Quit();
}



#endif // DEFS_H
