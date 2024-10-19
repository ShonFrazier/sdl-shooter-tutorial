/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include "common.h"

#include "draw.h"
#include "stage.h"
#include "util/list.h"

extern App   app;
extern Stage stage;

static void logic(void);
static void draw(void);
static void initPlayer(void);
static void fireBullet(void);
static void doPlayer(void);
static void doBullets(void);
static void drawPlayer(void);
static void drawBullets(void);

static Entity      *player;
static SDL_Texture *bulletTexture;

void initStage(void) {
	app.delegate.logic = ^() { logic(); };
	app.delegate.draw = ^() { draw(); };

	memset(&stage, 0, sizeof(Stage));

	ListAllocDefault(&(stage.fighters));
	ListAllocDefault(&(stage.bullets));

	initPlayer();

	bulletTexture = loadTexture("gfx/playerBullet.png");
}

static void initPlayer() {
	player = calloc(1, sizeof(Entity));
	ListAddItem(stage.fighters, player);

	player->x = 100;
	player->y = 100;
	player->texture = loadTexture("gfx/player.png");
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

static void logic(void) {
	doPlayer();
	doBullets();
}

static void doPlayer(void) {
	player->dx = player->dy = 0;

	if (player->reload > 0) {
		player->reload--;
	}

	if (app.keyboard[SDL_SCANCODE_UP]) {
		player->dy = -PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_DOWN]) {
		player->dy = PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_LEFT]) {
		player->dx = -PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_RIGHT]) {
		player->dx = PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_LCTRL] && player->reload == 0) {
		fireBullet();
	}

	player->x += player->dx;
	player->y += player->dy;
}

static void fireBullet(void) {
	Entity *bullet = calloc(1, sizeof(Entity));

	bullet->x = player->x + player->w;
	bullet->y = player->y + (player->h / 2) - (bullet->h / 2);
	bullet->dx = PLAYER_BULLET_SPEED;
	bullet->health = 1;

	bullet->texture = bulletTexture;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

	ListAddItem(stage.bullets, bullet);

	player->reload = 8;
}

static void doBullets(void) {
	List *filtered = ListFilter(stage.bullets, ^(void *ve) {
		Entity *e = ve;
		e->x += e->dx;
		e->y += e->dy;

		if (e->x <= SCREEN_WIDTH) {
			return (bool)true;
		} else {
			free(e); e = NULL;
			return (bool)false;
		}
	});

	List *oldBullets = stage.bullets;

	stage.bullets = filtered;

	ListFree(&oldBullets);
}

static void draw(void) {
	drawPlayer();
	drawBullets();
}

static void drawPlayer(void) {
	blit(player->texture, player->x, player->y);
}

static void drawBullets(void) {
	ListForEach(stage.bullets, ^(void *ve) {
		Entity *e = ve;
		blit(e->texture, e->x, e->y);
	});
}
