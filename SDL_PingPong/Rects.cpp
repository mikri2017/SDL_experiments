#include "Rects.h"

Rects::Rects()
{
    Rect.x = 0;
    Rect.y = 0;
    Rect.h = 0;
    Rect.w = 0;
}

void Rects::SetRectParams(int x, int y, int height, int width)
{
    Rect.x = x;
    Rect.y = y;
    Rect.h = height;
    Rect.w = width;
}

void Rects::getMinMaxXYParams(int &yMin, int &yMax, int &xMin, int &xMax)
{
    yMin = Rect.y;
    yMax = Rect.y + Rect.h;
    xMin = Rect.x;
    xMax = Rect.x + Rect.w;
}

void Rects::getHeightAndWidth(int &_Height, int &_Width)
{
    _Height = Rect.h;
    _Width = Rect.w;
}

void Rects::DrawRect(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderFillRect( renderer, &Rect );
}
