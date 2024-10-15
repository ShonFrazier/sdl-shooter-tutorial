#pragma once

#include "ctype.h"
#include "stdint.h"
#include "stdbool.h"
#include <SDL2/SDL.h>

void init_custom_events(void);
void doCustomEvents(SDL_Event *event);
