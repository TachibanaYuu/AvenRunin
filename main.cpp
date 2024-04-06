#include "defs.h"
#include "Graphics.h"
#include "player.h"
#include "timeControl.h"
#include "map.h"

TimeControl fps_timer;
Map gameMap;
Player gamePlayer;

int main(int argc, char** argv)
{
    initGameWindow();

    gameMap.loadMap();

    setUp(gamePlayer);

    while (game_Is_Running)
    {
        fps_timer.start();
        while (SDL_PollEvent(&game_event))
        {
            if (game_event.type == SDL_QUIT
                || (game_event.type == SDL_KEYDOWN
                    && game_event.key.keysym.sym == SDLK_ESCAPE))
            {
                quitGame();
            }
            gamePlayer.handleInput(game_event, game_Renderer);
        }
        gameMap.scrollMap();

        SDL_RenderClear(game_Renderer);

        gameMap.displayMap();

        gamePlayer.show(game_Renderer);

        gamePlayer.move();

        SDL_RenderPresent(game_Renderer);

        makeSmootherByFPS(fps_timer);
        }

    gameMap.clearMap();
    clearAll();

    return 0;
}


