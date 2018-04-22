#include "ScreenObjsMgr.h"

ScreenObjsMgr::ScreenObjsMgr()
{
    srand(time(NULL));

    XBegin = 0;
    ball.SetBallCenter(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    ball.SetBallRadius(BallRadius);
    ball.GenRandomDirection();
}

void ScreenObjsMgr::ChgXBegin(int Chg)
{
    XBegin += Chg;
    if( XBegin < 0 )
        XBegin = 0;
    if( XBegin > SCREEN_WIDTH - RectWidth )
        XBegin = SCREEN_WIDTH - RectWidth;
}

void ScreenObjsMgr::ChgXBeginByMouse(int NewXBegin)
{
    XBegin = NewXBegin - RectWidth/2;
    if( XBegin < 0)
        XBegin = 0;
    if( XBegin > SCREEN_WIDTH - RectWidth )
        XBegin = SCREEN_WIDTH - RectWidth;
}

void ScreenObjsMgr::PrepareScreen(SDL_Renderer* renderer)
{
    rectUp.SetRectParams( XBegin, 0, RectHeight, RectWidth );
    rectDown.SetRectParams( XBegin, SCREEN_HEIGHT - RectHeight, RectHeight, RectWidth );

    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderClear( renderer );

    rectUp.DrawRect( renderer );
    rectDown.DrawRect( renderer );

    ball.DrawCircle( renderer );
}

void ScreenObjsMgr::GoNextStep()
{
    ball.GoNextStepIfNeed();
    ball.CheckYStateForCollisionWithPlatform( rectUp );
    ball.CheckYStateForCollisionWithPlatform( rectDown );
}
