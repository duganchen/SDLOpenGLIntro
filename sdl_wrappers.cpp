#include "SDL.h"
#include "sdl_wrappers.h"

using namespace std;

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


GLContext::GLContext(shared_ptr<SDL_Window> window):
	context(nullptr)
{
	context = SDL_GL_CreateContext(window.get());
	if (nullptr == context)
	{
		throw runtime_error(SDL_GetError());
	}
}


GLContext::~GLContext()
{
	SDL_GL_DeleteContext(context);
}



Timer::Timer(Uint32 interval, SDL_TimerCallback callback, void* params):
	timerId(0)
{
	timerId = SDL_AddTimer(30, callback, nullptr);

	if (0 == timerId)
	{
		throw runtime_error(SDL_GetError());
	}
}


Timer::~Timer()
{
	SDL_RemoveTimer(timerId);
}


shared_ptr<SDL_Window> createWindow(const string title, int x, int y, int w, int h, Uint32 flags)
{
	auto rawWindow = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
	if (nullptr == rawWindow)
	{
		throw runtime_error(SDL_GetError());
	}
	return shared_ptr<SDL_Window>(rawWindow, SDL_DestroyWindow);
}
