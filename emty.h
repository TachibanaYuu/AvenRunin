class Map
{
public:
    void scroll(int distance);
    void setTexture(Graphics gameBackGround);
    void loadMap();
    void displayMap();
    void clearMap();
private:
    Graphics gameBackGround;
    Graphics gameGround;
    int scrollingOffset = 0;
    int width, height;
};

void Map::setTexture(Graphics gameBackGround) {

        SDL_QueryTexture(, NULL, NULL, &width, &height);
    }

void Map::scroll(int distance) {
        scrollingOffset -= distance;
        if( scrollingOffset < 0 ) { scrollingOffset = width; }
    }

void Map::loadMap()
{
 bool loadBackGround = gameBackGround.loadImg("img\\background.png", game_Renderer);
    if (!loadBackGround){
        logErrorAndExit("failed to load background", SDL_GetError());
        return;
    } else {
        bool loadGround = gameGround.loadImg("img\\ground2.png", game_Renderer);
        if (!loadGround){
            logErrorAndExit("failed to load ground", SDL_GetError());
            return;
        }
        gameGround.setRect(0, MAX_GROUND);
    }
}

void Map::clearMap()
{
    gameBackGround.cleanUp();
    gameGround.cleanUp();
}

void Map::displayMap()
{
    gameBackGround.render(game_Renderer, NULL);
    gameGround.render(game_Renderer);
}

