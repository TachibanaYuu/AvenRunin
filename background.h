#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "defs.h"

class Background
{
public:
    Background();
    ~Background();

    void loadTexture(std::string filepath,SDL_Renderer* game_Renderer);
    void setTexture();
    void scroll(int distance);
    void render();
    void renderTexture1();
    void renderTexture2();
    void cleanUp();
private:
    SDL_Texture* tex;
    int scrollingOffset;
    int width, height;
};

Background::Background()
{
    tex = nullptr;
    scrollingOffset = 0;
    width = 0;
    height = 0;
}

Background::~Background()
{
    cleanUp();
}

void Background::loadTexture(std::string filepath, SDL_Renderer* game_Renderer)
{
    SDL_Texture* new_texture = nullptr;
    SDL_Surface* surface = IMG_Load(filepath.c_str());
    if (surface == nullptr)
        logErrorAndExit("SDLCreatingSurface: ", SDL_GetError());
    else
    {
        new_texture = SDL_CreateTextureFromSurface(game_Renderer, surface);
        if (new_texture == nullptr)
            logErrorAndExit("SDLLoadTextureFromSurface: ", SDL_GetError());
        SDL_FreeSurface(surface);
    }
    tex = new_texture;
}

void Background::setTexture()
{
    SDL_QueryTexture(tex, NULL, NULL, &width, &height);
}

void Background::scroll(int distance)
{
    scrollingOffset -= distance;
    if (scrollingOffset < 0)
        scrollingOffset = width;
}

void Background::renderTexture1()
{
    SDL_Rect dest;
    dest.x = scrollingOffset;
    dest.y = 0;

    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(game_Renderer, tex, NULL, &dest);
}

void Background::renderTexture2()
{
    SDL_Rect dest;
    dest.x = scrollingOffset - width;
    dest.y = 0;

    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(game_Renderer, tex, NULL, &dest);
}

void Background::render()
{
    renderTexture1();
    renderTexture2();
}

void Background::cleanUp()
{
    if (tex != nullptr)
    {
        SDL_DestroyTexture(tex);
        tex = nullptr;
    }
}
#endif // BACKGROUND_H
