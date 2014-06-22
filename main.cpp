/*
 *  main.cpp
 *
 */

#include "GameApp.h"

int main(int argc, char *argv[])
{
    GameApp theGame;

    auto contextFlags = SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL;

    // Create a 640 by 480 window.
    theGame.InitializeSDL(640, 480, contextFlags);
    theGame.CreateOrthographicProjection(4.0, 3.0);
    theGame.InstallTimer();

	theGame.EventLoop();
    theGame.Cleanup();

    return 0;
}
