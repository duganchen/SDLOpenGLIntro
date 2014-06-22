#include <GL/gl.h>
#include "SDL.h"
#include "sdl_wrappers.h"

using namespace std;


int main(int argc, char *argv[])
{
	SDL();

	// Turn on double buffering.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Create a 640 by 480 window.
	const auto width = 640;
	const auto height = 480;
	auto contextFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	auto window = createWindow("SDL2 OpenGL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, contextFlags);
	GLContext context(window);

	// I use a near plane value of -1, and a far plane value of 1, which is what works best for 2D games.
	const auto projectionWidth = 4.0;
	const auto projectionHeight = 3.0;
	glOrtho(0.0, projectionWidth, 0.0, projectionHeight, -1.0, 1.0);

	SDL_Event event;

	auto done = false;
	while((!done) && (SDL_WaitEvent(&event)))
	{
		glClear(GL_COLOR_BUFFER_BIT); glColor3f(0.7, 0.5, 0.8);
		glRectf(1.0, 1.0, 3.0, 2.0);
		SDL_GL_SwapWindow(window.get());

		switch(event.type)
		{
			case SDL_KEYDOWN:
				// Quit when user presses a key.
				done = true;
				break;

			case SDL_QUIT:
				done = true;
				break;

			default:
				break;
		}

		SDL_Delay(30);
	}

	return 0;
}
