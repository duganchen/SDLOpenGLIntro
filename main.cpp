#include <GL/gl.h>
#include <stdexcept>
#include "SDL.h"

using namespace std;

const auto RUN_GAME_LOOP = 1;

Uint32 GameLoopTimer(Uint32 interval, void* param)
{
    // Create a user event to call the game loop.
    SDL_Event event;

    event.type = SDL_USEREVENT;
    event.user.code = RUN_GAME_LOOP;
    event.user.data1 = 0;
    event.user.data2 = 0;

    SDL_PushEvent(&event);

    return interval;
}


class SDL
{
public:
    SDL();
	~SDL();
};


SDL::SDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		throw runtime_error(SDL_GetError());
	}
}


SDL::~SDL()
{
    SDL_Quit();
}



int main(int argc, char *argv[])
{
    // GameApp theGame;

    auto contextFlags = SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL;

    // Create a 640 by 480 window.
    // theGame.InitializeSDL(640, 480, contextFlags);
	const auto width = 640;
	const auto height = 480;

	SDL();

    // Turn on double buffering.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Create the window
    auto mainWindow = SDL_CreateWindow("SDL2 OpenGL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, contextFlags);
    auto mainGLContext = SDL_GL_CreateContext(mainWindow);

	const auto projectionWidth = 4.0;
	const auto projectionHeight = 3.0;

    // I use a near plane value of -1, and a far plane value of 1, which is what works best for 2D games.
    glOrtho(0.0, projectionWidth, 0.0, projectionHeight, -1.0, 1.0);

    auto timer = SDL_AddTimer(30, GameLoopTimer, nullptr);

    SDL_Event event;

	auto done = false;
    while((!done) && (SDL_WaitEvent(&event))) {
        switch(event.type) {
            case SDL_USEREVENT:
				switch (event.user.code)
				{
    			    case RUN_GAME_LOOP:
						glClear(GL_COLOR_BUFFER_BIT);
    					glColor3f(0.7, 0.5, 0.8);
    					glRectf(1.0, 1.0, 3.0, 2.0);
    					SDL_GL_SwapWindow(mainWindow);
    			        break;
    			    default:
    			        break;
    			}
                break;

            case SDL_KEYDOWN:
                // Quit when user presses a key.
                done = true;
                break;

            case SDL_QUIT:
                done = true;
                break;

            default:
                break;
        }   // End switch

    }   // End while


    SDL_bool success;
    success = SDL_RemoveTimer(timer);

    SDL_GL_DeleteContext(mainGLContext);
    SDL_DestroyWindow(mainWindow);

    return 0;
}
