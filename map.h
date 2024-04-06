#ifndef MAPS_H
#define MAPS_H

#include "defs.h"
#include "Graphics.h"
#include "background.h"

class Map
{
public:
    void loadMap();
    void displayMap();
    void scrollMap();
    void clearMap();
private:
    Background gameBackGround;
    Graphics gameGround;
};

void Map::loadMap()
{
        bool loadGround = gameGround.loadImg("img\\ground2.png", game_Renderer);
        if (!loadGround){
            logErrorAndExit("failed to load ground", SDL_GetError());
            return;
        }
        gameGround.setRect(0, MAX_GROUND);

        gameBackGround.loadTexture("img\\background.png", game_Renderer);
        gameBackGround.setTexture();
}


void Map::clearMap()
{
    gameBackGround.cleanUp();
    gameGround.cleanUp();
}

void Map::displayMap()
{
    gameBackGround.render();
    gameGround.render(game_Renderer);
}

void Map::scrollMap()
{
    gameBackGround.scroll(4);
}

#endif // MAPS_H
