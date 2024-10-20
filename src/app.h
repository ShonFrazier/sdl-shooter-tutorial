#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpragma-once-outside-header"
#pragma once
#pragma clang diagnostic pop

#include <SDL2/SDL.h>
#include "util/util.h"
#include "vec2.h"
#include "defs.h"

typedef struct {
	void (^logic)(void);
	void (^draw)(void);
} Delegate;

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window   *window;
	Vec2          delta;
	int           up;
	int           down;
	int           left;
	int           right;
	int           fire;
	Delegate      delegate;
	int           keyboard[MAX_KEYBOARD_KEYS];
} App;

App *AppAlloc(void);
