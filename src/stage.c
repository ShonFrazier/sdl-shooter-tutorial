#include <stdio.h>
#include <Block.h>
#include <SDL2/SDL_render.h>
#include "util/list.h"
#include "common.h"
#include "util/memory.h"
#include "defs.h"
#include "draw.h"
#include "stage.h"
#include "entity.h"

static void logic(App *, Stage *);
static void draw(Stage *);
static void initPlayer(const Stage *);
static void fireBullet(Stage *);
static void doPlayer(App *, Stage *);
static void doFighters(Stage *);
static void doBullets(Stage *);
static void drawPlayer(SDL_Renderer *);
static void drawBullets(Stage *);
static void drawFighters(Stage *);
static void spawnEnemies(Stage *);

static Entity      *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;

Stage *StageAlloc(App *app) {
	Stage *stage = calloc(1, sizeof(Stage));
	stage->app = app;

	ListAllocDefault(&(stage->fighters));
	ListAllocDefault(&(stage->bullets));

	app->delegate.logic = Block_copy(^() { logic(app, stage); });
	app->delegate.draw = Block_copy(^() { draw(stage); });

	initPlayer(stage);

	bulletTexture = loadTexture(app->renderer, "gfx/playerBullet.png");
	enemyTexture = loadTexture(app->renderer, "gfx/enemy.png");

	return stage;
}

static void initPlayer(const Stage *stage) {
	player = EntityAlloc();
	ListAddItem(stage->fighters, player);

	player->team = TeamPlayer;
	player->health = 1;
	player->x = 100;
	player->y = 100;
	player->texture = loadTexture(stage->app->renderer, "gfx/player.png");
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

static void logic(App *app, Stage *stage) {
	doFighters(stage);
	doPlayer(app, stage);
	doBullets(stage);
	spawnEnemies(stage);
}

static void doPlayer(App *app, Stage *stage) {
	player->dx = player->dy = 0;

	if (player->reload > 0) {
		player->reload--;
	}

	if (app->keyboard[SDL_SCANCODE_UP]) {
		player->dy = -PLAYER_SPEED;
	}

	if (app->keyboard[SDL_SCANCODE_DOWN]) {
		player->dy = PLAYER_SPEED;
	}

	if (app->keyboard[SDL_SCANCODE_LEFT]) {
		player->dx = -PLAYER_SPEED;
	}

	if (app->keyboard[SDL_SCANCODE_RIGHT]) {
		player->dx = PLAYER_SPEED;
	}

	if (app->keyboard[SDL_SCANCODE_SPACE] && player->reload == 0) {
		fireBullet(stage);
	}

	player->x += player->dx;
	player->y += player->dy;
}

static void doFighters(Stage *stage) {
	List *filtered = ListFilter(stage->fighters, ^(void *ve) {
		Entity *e = ve;
		e->x += e->dx;
		e->y += e->dy;

		if (e != player && e->x < -e->w || e->health <= 0) {
			// The list doesn't own the item and it is not
			// being copied to the new list. Free it.
			EntityFree(&e);
			return (bool)false;
		}

		return (bool)true;
	});

	List *old = stage->fighters;
	stage->fighters = filtered;
	ListFree(&old);
}

static void spawnEnemies(Stage *stage) {
	stage->enemySpawnTimer -= 1;
	if (stage->enemySpawnTimer <= 0) {
		Entity *enemy = EntityAlloc();
		enemy->team = TeamPig;
		enemy->health = 1;
		enemy->x = SCREEN_WIDTH;
		enemy->y = rand() % SCREEN_HEIGHT;
		enemy->texture = enemyTexture;

		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

		enemy->dx = -(2 + (rand() % 4));

		stage->enemySpawnTimer = 50 + (rand() % 60);

		ListAddItem(stage->fighters, enemy);
	}
}

static void fireBullet(Stage *stage) {
	Entity *bullet = EntityAlloc();

	bullet->team = TeamPlayer;
	bullet->x = player->x + player->w;
	bullet->y = player->y + ((int)(player->h / 2) - (int)(bullet->h / 2));
	bullet->dx = PLAYER_BULLET_SPEED;
	bullet->health = 1;

	bullet->texture = bulletTexture;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

	ListAddItem(stage->bullets, bullet);

	player->reload = 8;
}

static bool bulletHitFighter(Entity *bullet, List *fighters) {
	for(
		ListNode *node = ItrListStartNode(fighters);
		node != NULL;
		node = ItrListNodeNext(node)
	) {
		Entity *fighter = (Entity *)ItrListNodeGetItem(node);
		if (fighter->team != bullet->team && fighter->doesCollideWith(bullet)) {
			bullet->health = 0;
			fighter->health = 0;

			return true;
		}
	}
	return false;
}

static void doBullets(Stage *stage) {
	List *filtered = ListFilter(stage->bullets, ^(void *ep) {
		Entity *bullet = ep;
		bullet->x += bullet->dx;
		bullet->y += bullet->dy;

		if (bulletHitFighter(bullet, stage->fighters) || bullet->x > SCREEN_WIDTH) {
			free(bullet); bullet = NULL;
			return (bool)false;
		} else {
			return (bool)true;
		}
	});

	List *old = stage->bullets;
	stage->bullets = filtered;
	ListFree(&old);
}

static void draw(Stage *stage) {
	drawPlayer(stage->app->renderer);
	drawBullets(stage);
	drawFighters(stage);
}

static void drawPlayer(SDL_Renderer *renderer) {
	blit(renderer, player->texture, player->x, player->y);
}

static void drawBullets(Stage *stage) {
	ListForEach(stage->bullets, ^(void *ve) {
		Entity *e = ve;
		blit(stage->app->renderer, e->texture, e->x, e->y);
	});
}

static void drawFighters(Stage *stage) {
	ListForEach(stage->fighters, ^(void *ve) {
		Entity *e = ve;
		blit(stage->app->renderer, e->texture, e->x, e->y);
	});
}
