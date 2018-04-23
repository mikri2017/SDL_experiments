#ifndef SDL_GAME_H_INCLUDED
#define SDL_GAME_H_INCLUDED

#include <string>
#include "MainConstants.h"
#include "ScreenObjsMgr.h"

class SDL_Game
{
private:
    SDL_Window* window;
	SDL_Renderer* renderer;
	ScreenObjsMgr ScrObjMngr;
	std::string SDL_error_msg;
public:
    SDL_Game();
    std::string getErrorMsg();
    bool init(const char* title, int xpos, int ypos,
              int height, int width, int flags);
    int process_events();
    void render();
    void clean_and_exit();
};

#endif // SDL_GAME_H_INCLUDED
