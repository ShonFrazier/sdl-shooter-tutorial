/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */
#pragma once

#include <SDL2/SDL.h>

void         prepareScene(void);
void         presentScene(void);
SDL_Texture *loadTexture(char *filename);
void         blit(SDL_Texture *texture, int x, int y);
