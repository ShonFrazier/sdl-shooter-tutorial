/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */
#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "defs.h"
#include "util/list.h"

typedef struct {
	int x;
	int y;
} Vec2;

typedef struct {
	void (^logic)(void);
	void (^draw)(void);
} Delegate;

Vec2 vec2_add_vec2(Vec2 v1, Vec2 v2);
Vec2 vec2_add_int (Vec2 v1, int i);
Vec2 vec2_sub_vec2(Vec2 v1, Vec2 v2);
Vec2 vec2_sub_int (Vec2 v1, int i);
Vec2 vec2_mul_vec2(Vec2 v1, Vec2 v2);
Vec2 vec2_mul_int (Vec2 v1, int i);

static const Vec2 DELTA_ZERO  = { .x= 0, .y= 0 };
static const Vec2 DELTA_ONE   = { .x= 1, .y= 1 };
static const Vec2 DELTA_NEG   = { .x=-1, .y=-1 };
static const Vec2 DELTA_UP    = { .x= 0, .y=-1 };
static const Vec2 DELTA_DOWN  = { .x= 0, .y= 1 };
static const Vec2 DELTA_LEFT  = { .x=-1, .y= 0 };
static const Vec2 DELTA_RIGHT = { .x= 1, .y= 0 };

typedef enum {
	DirectionNone = 0,
	DirectionEast = 1,
	DirectionNorthEast = 2,
	DirectionNorth = 3,
	DirectionNorthWest = 4,
	DirectionWest = 5,
	DirectionSouthWest = 6,
	DirectionSouth = 7,
	DirectionSouthEast = 8
} Direction;

static const Vec2 Directions[] = {
	{ .x= 0, .y= 0 },
	{ .x= 1, .y= 0 },
	{ .x= 1, .y=-1 },
	{ .x= 0, .y=-1 },
	{ .x=-1, .y=-1 },
	{ .x=-1, .y= 0 },
	{ .x=-1, .y= 1 },
	{ .x= 0, .y= 1 },
	{ .x= 1, .y= 1 },
};

Vec2 DirectionVector(Direction d);

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

typedef struct Entity Entity;
struct Entity {
	bool         fromPool;
	bool         used;
	float        x;
	float        y;
	int          w;
	int          h;
	float        dx;
	float        dy;
	int          health;
	int          reload;
	SDL_Texture *texture;
	Entity      *next;
};

typedef struct {
	List *fighters;
	List *bullets;
	List *enemies;
	int enemySpawnTimer;
} Stage;
