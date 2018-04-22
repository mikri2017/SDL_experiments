/*
    Рыжков Михаил, Пинг-Понг на SDL
 */

#include <iostream>
#include <SDL.h>
#include <SDL_mouse.h>
#include <SDL_keyboard.h>
#include "MainConstants.h"
#include "ScreenObjsMgr.h"

ScreenObjsMgr ScrObjMngr;

static int process_events()
{
    SDL_Event event;
    int ret = 1;

    while ( SDL_PollEvent(&event) >= 1)
    {
        switch(event.type)
        {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_LEFT)
                ScrObjMngr.ChgXBegin(-RectStepByKeyboard);

            if (event.key.keysym.sym == SDLK_RIGHT)
                ScrObjMngr.ChgXBegin(RectStepByKeyboard);

            if (event.key.keysym.sym == SDLK_ESCAPE)
                ret = 0;
            break;
        case SDL_MOUSEMOTION:
            ScrObjMngr.ChgXBeginByMouse(event.motion.x);
            break;
        default:
            break;
        }
    }
    return ret;
}

void updateScreen(SDL_Renderer* renderer)
{
    ScrObjMngr.PrepareScreen(renderer);
    ScrObjMngr.GoNextStep();
    SDL_RenderPresent(renderer);
}

int main( int argc, char* args[] )
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	// Инициализация SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
	else
	{
	    std::cout << "Press Esc button to Exit!\n";
		// Создаем окно
		window = SDL_CreateWindow( "SDL PingPong by MIKRI (Press Esc for Exit)", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN );
		if( window == NULL )
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError();
        else
        {
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

            while(process_events())
                updateScreen(renderer);
        }
	}

	SDL_DestroyWindow( window ); // Уничтожаем окно
	SDL_Quit(); //Выход из SDL

	return 0;
}
