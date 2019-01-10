#include <SDL.h>

#include "Crew.h"
#include "Window.h"

SDL_Renderer *renderer = NULL;

const char *platform = NULL;

/*	Method that renders the Window and checks to see if the 
	player has clicked the QUIT button. If so, we tear down the 
	app.	*/
static CrewStatus WindowUpdate(Crew *c) {
	static Uint32 start = 0;

	Uint32 elapsed = SDL_GetTicks() - start;
	if (elapsed < WINDOW_TICKS) SDL_Delay(WINDOW_TICKS-elapsed);

	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);

	start = SDL_GetTicks();

	return LIVE;
}

/*	Method that deallocates the SDL_Renderer and 
	SDL_Window.	*/
static CrewStatus WindowDestroy(Crew *c) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return CUT;
}

/*	Method that initialises the Window Crew member.	*/
CrewStatus WindowInit(Crew *c) {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		puts("failed to create window");
		return EXIT;
	}

	platform = SDL_GetPlatform();

        window = SDL_CreateWindow(
		"soda: SDL",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT, 
		SDL_WINDOW_SHOWN
	);

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	SDL_SetWindowFullscreen(window, 0);

	c->tag = "window";
	c->update = WindowUpdate;
	c->destroy = WindowDestroy;

	return LIVE;
}

SDL_Renderer *WindowGetRenderer() {
	return renderer;
}
