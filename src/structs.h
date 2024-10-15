/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include <SDL2/SDL.h>

typedef struct {
	int x;
	int y;
} Vec2;

Vec2 vec2_add(Vec2 v1, Vec2 v2);
Vec2 vec2_multiply(Vec2 v1, Vec2 v2);

static const Vec2 DELTA_ZERO  = { .x= 0, .y= 0 };
static const Vec2 DELTA_ONE   = { .x= 1, .y= 1 };
static const Vec2 DELTA_NEG   = { .x=-1, .y=-1 };
static const Vec2 DELTA_UP    = { .x= 0, .y=-1 };
static const Vec2 DELTA_DOWN  = { .x= 0, .y= 1 };
static const Vec2 DELTA_LEFT  = { .x=-1, .y= 0 };
static const Vec2 DELTA_RIGHT = { .x= 1, .y= 0 };

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window   *window;
	int           up;
	int           down;
	int           left;
	int           right;
	Vec2          delta;
} App;

typedef struct {
	int          x;
	int          y;
	SDL_Texture *texture;
} Entity;
