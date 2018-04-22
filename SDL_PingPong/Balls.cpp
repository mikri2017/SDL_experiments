#include "Balls.h"

Balls::Balls()
{
    xCenter = 0;
    yCenter = 0;
    Radius = 0;
    lenDirectionLine = 0;
    last_time = clock();

    CalculateAngles();
}

void Balls::CalculateAngles()
{
    for(int i=0; i<360; i++)
    {
        CosForAngles.push_back(cos(i*PI_by_180));
        SinForAngles.push_back(sin(i*PI_by_180));
    }
}

void Balls::FindAndSetRealAngle()
{
    while(angle < 0)
        angle = angle + 360;
    while(angle >= 360)
        angle = angle - 360;
}

bool Balls::SetBallCenter(int x, int y)
{
    if (xCenter < 0 || yCenter < 0)
        return false;

    xCenter = x;
    yCenter = y;

    return true;
}

bool Balls::SetBallRadius(int R)
{
    if (R < 0)
        return false;

    Radius = R;
    return true;
}

void Balls::DrawCircle(SDL_Renderer* renderer)
{
    int XDest, YDest;

    xMin = xCenter - Radius;
    xMax = xCenter + Radius;
    yMin = yCenter - Radius;
    yMax = yCenter + Radius;

    for(int i=0;i<360;i++)
    {
        XDest = xCenter+CosForAngles[i]*Radius;
        YDest = yCenter+SinForAngles[i]*Radius;
        SDL_RenderDrawLine(renderer,xCenter,yCenter,XDest,YDest);
    }
}

void Balls::SetDirectionAngle(double new_angle)
{
    if(new_angle < 0)
        new_angle = new_angle + 360;

    angle = new_angle;

    if( angle > 360)
        FindAndSetRealAngle();
}

void Balls::GoNextStepIfNeed()
{
    unsigned int cur_time = clock();
    if (cur_time - last_time >= WaitTimeBeforeNextStep) // „тобы все происходило не слишком быстро...
    {
        // ѕеремещаем шарик вдоль выбранной направл€ющей
        lenDirectionLine++;
        xCenter = xCenter + CosForAngles[angle] * lenDirectionLine;
        yCenter = yCenter + SinForAngles[angle] * lenDirectionLine;

        last_time = cur_time;
    }
    CheckYStateAndReInit();
    CheckXStateAndChgDirection();
}

void Balls::GenRandomDirection()
{
    // „тобы не возникало случа€, когда шарик движетс€
    // параллельно ракеткам и игрок не может на него повли€ть
    angle = rand()%360;
    if(angle == 0 || angle == 180 || angle == 90) // ѕлюс, при строгом перпендикул€ре к ракеткам, играть не интересно...
        angle = angle + 45;
}

void Balls::CheckYStateAndReInit()
{
    // Ўарик укатилс€ вверх или вниз за экран
    if(yMin < 0 || yMax > SCREEN_HEIGHT)
    {
        SetBallCenter(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
        lenDirectionLine = 0;
        GenRandomDirection();
    }
}

void Balls::CheckYStateForCollisionWithPlatform(Rects &Rect)
{
    // ѕровер€ем столкновение с ракеткой
    int r_xMin, r_xMax, r_yMin, r_yMax;
    int r_Height, r_Width;

    Rect.getMinMaxXYParams(r_yMin,r_yMax,r_xMin,r_xMax);
    Rect.getHeightAndWidth(r_Height,r_Width);

    if( ((xMin >= r_xMin) && (xMax <= r_xMax)) )
    {
        if( (yMin <= r_yMax) && (yMax >= r_yMin) )
        {
            lenDirectionLine = 0;

            SetDirectionAngle(360 - angle);

            if(r_yMax == r_Height)
                yCenter = yCenter + 5;

            if(r_yMin == SCREEN_HEIGHT - r_Height)
                yCenter = yCenter - 5;
        }
    }
}

void Balls::CheckXStateAndChgDirection()
{
    // ѕровер€ем столкновени€ с боковыми стенками
    if(xMin <= 0 || xMax >= SCREEN_WIDTH)
    {
        lenDirectionLine = 0;

        SetDirectionAngle(180 - angle);

        if(xMin < 0)
            xCenter = Radius + 1;
        else xCenter = SCREEN_WIDTH - Radius - 1;
    }
}
