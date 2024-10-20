#include <SDL2/SDL_image.h>
#include "common.h"
#include "init.h"
#include "app.h"

typedef struct {
	App *app;
} StaticState;

StaticState staticState;

void initSDL(App *app) {
	staticState.app = app;
	int rendererFlags = SDL_RENDERER_ACCELERATED;
	int windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	app->window = SDL_CreateWindow("Shooter 05", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	app->renderer = SDL_CreateRenderer(app->window, -1, rendererFlags);

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void cleanup(void)
{
	IMG_Quit();
	SDL_DestroyRenderer(staticState.app->renderer);
	SDL_DestroyWindow(staticState.app->window);
	SDL_Quit();
}
