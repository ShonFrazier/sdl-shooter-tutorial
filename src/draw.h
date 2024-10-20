#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpragma-once-outside-header"
#pragma once
#pragma clang diagnostic pop

#include <SDL2/SDL.h>

void         prepareScene(SDL_Renderer *);
void         presentScene(SDL_Renderer *);
SDL_Texture *loadTexture(SDL_Renderer *, char *filename);
void         blit(SDL_Renderer *, SDL_Texture *texture, int x, int y);
