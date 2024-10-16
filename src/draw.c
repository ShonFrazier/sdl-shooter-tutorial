/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include <SDL2/SDL_image.h>
#include "common.h"
#include "draw.h"

extern App app;

void prepareScene(void) {
	SDL_SetRenderDrawColor(app.renderer, 32, 32, 32, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void) {
	SDL_RenderPresent(app.renderer);
}

SDL_Texture *loadTexture(char *filename) {
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	return IMG_LoadTexture(app.renderer, filename);
}

void blit(SDL_Texture *texture, int x, int y) {
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}
