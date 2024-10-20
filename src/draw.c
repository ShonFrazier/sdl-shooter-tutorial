#include <SDL2/SDL_image.h>
#include "SDL2/SDL_render.h"
#include "common.h"
#include "draw.h"
#include "app.h"

void prepareScene(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
	SDL_RenderClear(renderer);
}

void presentScene(SDL_Renderer *renderer) {
	SDL_RenderPresent(renderer);
}

SDL_Texture *loadTexture(SDL_Renderer *renderer, char *filename) {
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	return IMG_LoadTexture(renderer, filename);
}

void blit(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y) {
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}
