#ifndef RECTS_H_INCLUDED
#define RECTS_H_INCLUDED

#include <SDL.h>

class Rects
{
private:
    SDL_Rect Rect;
public:
    Rects();
    void SetRectParams(int x, int y, int height, int width);
    void getMinMaxXYParams(int &yMin, int &yMax, int &xMin, int &xMax);
    void getHeightAndWidth(int &_Height, int &_Width);
    void DrawRect(SDL_Renderer* renderer);
};

#endif // RECTS_H_INCLUDED
