#ifndef SDL_WRAPPERS_H
#define SDL_WRAPPERS_H

#include <memory>
#include <string>

// Exception-safe wrapper classes for SDL2 types that we can't handle
// with smart pointers.

class SDL
{
public:
    SDL();
	~SDL();
};


class GLContext
{
public:
	GLContext(std::shared_ptr<SDL_Window>);
	~GLContext();
private:
	SDL_GLContext context;
};


// And exception-safe factory functions for SDL2 types that we can.

std::shared_ptr<SDL_Window> createWindow(const std::string, int, int, int, int, Uint32 flags);


// And other functions that need exception handling.

void waitEvent(SDL_Event *);

#endif
