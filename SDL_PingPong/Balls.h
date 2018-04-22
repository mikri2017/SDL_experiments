#ifndef BALLS_H_INCLUDED
#define BALLS_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <ctime>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "MainConstants.h"
#include "Rects.h"

class Balls
{
private:
    const unsigned int WaitTimeBeforeNextStep = 50; // Миллисекунды, влияет на скорость игры(движения шарика)
    double xCenter, yCenter;
    double Radius;
    int angle;
    double lenDirectionLine;
    double xMin, xMax, yMin, yMax;
    unsigned int last_time;
    std::vector<double> CosForAngles, SinForAngles;
    void SetDirectionAngle(double new_angle);
    void CalculateAngles();
public:
    Balls();
    void FindAndSetRealAngle();
    bool SetBallCenter(int x, int y);
    bool SetBallRadius(int R);
    void DrawCircle(SDL_Renderer* renderer);
    void GenRandomDirection();
    void GoNextStepIfNeed();
    void CheckYStateForCollisionWithPlatform(Rects& Rect);
    void CheckYStateAndReInit();
    void CheckXStateAndChgDirection();
};

#endif // BALLS_H_INCLUDED
