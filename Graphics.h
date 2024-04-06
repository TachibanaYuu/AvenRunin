#pragma once

#include "defs.h"


class Graphics
{
protected:
    SDL_Texture* gTexture;
    SDL_Rect gRect;
public:
    Graphics();
    ~Graphics();

    void setRect(const int& x, const int& y);
    SDL_Rect getRect();
    SDL_Texture* getTexture();
    virtual bool loadImg(std::string filepath, SDL_Renderer* game_Renderer);
    void render(SDL_Renderer* res, const SDL_Rect* clip = NULL);
    void cleanUp();
};

Graphics::Graphics()
{
    gTexture = NULL;
    gRect.x=0;
    gRect.y=0;
    gRect.w=0;
    gRect.h=0;
}

Graphics::~Graphics()
{
    cleanUp();
}

void Graphics::setRect(const int& x, const int& y)
{
    gRect.x = x;
    gRect.y = y;
}

SDL_Rect Graphics::getRect()
{
    return gRect;
}

SDL_Texture* Graphics::getTexture()
{
    return gTexture;
}
bool Graphics::loadImg(std::string filepath, SDL_Renderer* game_Renderer)
{
        SDL_Texture* newTexture = nullptr;
        SDL_Surface*  loadSurface = IMG_Load(filepath.c_str());
        if (loadSurface == NULL)
                logErrorAndExit("Load filepath to surface: ", SDL_GetError());
        else {
            newTexture = SDL_CreateTextureFromSurface(game_Renderer, loadSurface);
            if (newTexture == NULL)
                logErrorAndExit("Update texture from surface: " , SDL_GetError());
                //std::cout << "HEllo world" << std::endl;
            else{
                gRect.w = loadSurface->w;
                gRect.h = loadSurface->h;
            }
            SDL_FreeSurface(loadSurface);
        }
        gTexture = newTexture;
        return (gTexture != nullptr);
}

void Graphics::render(SDL_Renderer* res, const SDL_Rect* clip /*=NULL*/)
{
    SDL_Rect dst = {gRect.x, gRect.y, gRect.w, gRect.h};

    SDL_RenderCopy(res, gTexture, clip, &dst);

}

void Graphics::cleanUp()
{
    if (gTexture != NULL){
        SDL_DestroyTexture(gTexture);
        gTexture = NULL;
        gRect.w=0;
        gRect.h=0;
    }
}

