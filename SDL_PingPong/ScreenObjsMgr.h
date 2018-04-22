#ifndef SCREENOBJSMGR_H_INCLUDED
#define SCREENOBJSMGR_H_INCLUDED

#include "Balls.h"
#include "Rects.h"
#include "MainConstants.h"

class ScreenObjsMgr
{
private:
    Balls ball;
    Rects rectUp, rectDown;
    int XBegin;
    const int RectWidth = 200;
    const int RectHeight = 50;
    const int BallRadius = 20;
public:
    ScreenObjsMgr();
    void ChgXBegin(int Chg);
    void ChgXBeginByMouse(int NewXBegin);
    void PrepareScreen(SDL_Renderer* renderer);
    void GoNextStep();
};

#endif // SCREENOBJSMGR_H_INCLUDED
