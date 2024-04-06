#ifndef PLAYER_H
#define PLAYER_H

#include "defs.h"
#include "Graphics.h"


struct Input{
    int right_;
    int left_;
    int jump_;
};

class Player : public Graphics
{
private:
    float dx, dy;
    float x_pos, y_pos;
    int width_frame, height_frame;

    SDL_Rect frame_clip[4];
    Input input_type;
    int frame_;

    bool is_jumping;

public:
    Player();
    ~Player();

    bool loadImg(std::string filepath, SDL_Renderer* game_Renderer);
    void setClips();
    void show(SDL_Renderer* game_Renderer);
    void handleInput(SDL_Event game_event, SDL_Renderer* game_Renderer);
    void move();

};

Player::Player()
{
    frame_ = 0;
    x_pos = CHARACTER_X_POS;
    y_pos = CHARACTER_Y_POS;
    dx = 0;
    dy = 0;
    width_frame = 0;
    height_frame = 0;
    input_type.right_ = 0;
    input_type.left_ = 0;
    input_type.jump_ = 0;
}

Player::~Player()
{

}

bool Player::loadImg(std::string filepath, SDL_Renderer* game_Renderer)
{
    bool res = Graphics::loadImg(filepath, game_Renderer);
    if (res)
    {
        width_frame = gRect.w / MAX_FRAME;
        height_frame = gRect.h;
    }
}

void Player::setClips()
{
    if (width_frame > 0 && height_frame > 0)
    {
        frame_clip[0].x = 0;
        frame_clip[0].y = 0;
        frame_clip[0].w = width_frame;
        frame_clip[0].h = height_frame;

        for (int i = 1; i < MAX_FRAME; i++) {
            frame_clip[i].x = i * width_frame;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }
    }
}

void Player::show(SDL_Renderer* game_Renderer)
{
    loadImg("img\\diamondheadGo.png", game_Renderer);
    if (input_type.right_ == 1
        || input_type.left_ == 1)
        frame_++;
    else
        frame_ = 0;

    if (frame_ >= MAX_FRAME){
        frame_ = 0;
    }

    gRect.x = x_pos;
    gRect.y = y_pos;
    SDL_Rect* current_clip = &frame_clip[frame_];
    SDL_Rect renderRes = {gRect.x, gRect.y, width_frame, height_frame};

    SDL_RenderCopy(game_Renderer, gTexture, current_clip, &renderRes);
}

void Player::handleInput(SDL_Event game_event, SDL_Renderer* game_Renderer)
{
    if (game_event.type == SDL_KEYDOWN)
    {
        switch (game_event.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                input_type.right_ = 1;
                input_type.left_ = 0;
            }
            break;
        case SDLK_LEFT:
            {
                input_type.left_ = 1;
                input_type.right_ = 0;
            }
            break;
        case SDLK_UP:
            {
                input_type.jump_ = 1;
            }
            break;
        case SDLK_SPACE:
            {
                input_type.jump_ = 1;
            }
            break;
        }
    }
    else if (game_event.type == SDL_KEYUP)
    {
        switch (game_event.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                input_type.right_ = 0;
            }
            break;
        case SDLK_LEFT:
            {
                input_type.left_ = 0;
            }
            break;
        case SDLK_UP:
            {
                input_type.jump_ = 0;
            }
            break;
        case SDLK_SPACE:
            {
                input_type.jump_ = 0;
            }
            break;
        }
    }
}

void Player::move()
{
    if (input_type.right_ == 1){
    dx = PLAYER_SPEED;
    dy = 0;

        x_pos += dx;
        y_pos += dy;

        if (x_pos+dx >= SCREEN_WIDTH)
        {
            x_pos = 10;
        }
    }
    if (input_type.left_ == 1){
        dx = PLAYER_SPEED;
        dy = 0;

        x_pos -= dx;
        y_pos += dy;

        if (x_pos+dx <= 0)
        {
            x_pos = 10;
        }
    }
    if (y_pos < 280){
        y_pos = 280;
    }
    if (input_type.jump_ == 1)
    {
        y_pos -= 120;
        input_type.jump_ = 0;
    }
}

void setUp(Player &gamePlayer)
{
    gamePlayer.loadImg("img\\diamondheadGo.png", game_Renderer);
    gamePlayer.setClips();
}

#endif // PLAYER_H
