#ifndef TIMECONTROL_H
#define TIMECONTROL_H

#include "defs.h"

class TimeControl
{
public:
    TimeControl();
    ~TimeControl();

    void start();
    void stop();
    void paused();
    void unpaused();

    int get_ticks();
    bool is_started();
    bool is_paused();
private:
    int start_tick;
    int paused_tick;

    bool is_paused_;
    bool is_started_;
};

TimeControl::TimeControl()
{
    start_tick = 0;
    paused_tick = 0;
    is_paused_ = false;
    is_started_ = false;
}

TimeControl::~TimeControl()
{

}

void TimeControl::start()
{
    is_started_ = true;
    is_paused_ = false;
    start_tick = SDL_GetTicks();
}

void TimeControl::stop()
{
    is_paused_ = false;
    is_started_ = false;
}

void TimeControl::paused()
{
    if (is_started_ == true && is_paused_ == false)
    {
        is_paused_ = true;
        paused_tick = SDL_GetTicks() - start_tick;
    }
}

void TimeControl::unpaused()
{
    if (is_paused_ == true)
    {
        is_paused_ = false;
        start_tick = SDL_GetTicks() - paused_tick;
        paused_tick = 0;
    }
}

int TimeControl::get_ticks()
{
    if (is_started_ == true)
    {
        if (is_paused_ == true)
        {
            return paused_tick;
        }
        else
        {
            return SDL_GetTicks() - start_tick;
        }
    }
    return 0;
}

bool TimeControl::is_started()
{
    return is_started_;
}

bool TimeControl::is_paused()
{
    return is_paused_;
}

void makeSmootherByFPS(TimeControl& fps_timer)
{
    int realTime = fps_timer.get_ticks();
    int timeOneFrame = ONE_SECOND / FRAME_PER_SECOND;
    if (realTime < timeOneFrame)
    {
        int delayTime = timeOneFrame - realTime;
        SDL_Delay(delayTime);
    }
}
#endif // TIMECONTROL_H
