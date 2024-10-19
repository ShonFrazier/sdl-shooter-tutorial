#include "util/list.h"
#include "common.h"
#include "util/memory.h"
#include "defs.h"
#include "draw.h"
#include "stage.h"
#include "entity.h"

extern App   app;
extern Stage stage;

static void logic(void);
static void draw(void);
static void initPlayer(void);
static void fireBullet(void);
static void doPlayer(void);
static void doFighters(void);
static void doBullets(void);
static void drawPlayer(void);
static void drawBullets(void);
static void drawFighters(void);
static void spawnEnemies(void);

static Entity      *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;

void initStage(void) {
	app.delegate.logic = ^() { logic(); };
	app.delegate.draw = ^() { draw(); };

	memset(&stage, 0, sizeof(Stage));

	ListAllocDefault(&(stage.fighters));
	ListAllocDefault(&(stage.bullets));

	initPlayer();

	bulletTexture = loadTexture("gfx/playerBullet.png");
	enemyTexture = loadTexture("gfx/enemy.png");
}

static void initPlayer() {
	player = EntityAlloc();
	ListAddItem(stage.fighters, player);

	player->team = TeamPlayer;
	player->x = 100;
	player->y = 100;
	player->texture = loadTexture("gfx/player.png");
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

static void logic(void) {
	doPlayer();
	doFighters();
	doBullets();
	spawnEnemies();
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

static void doFighters(void) {
	List *filtered = ListFilter(stage.fighters, ^(void *ve) {
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

	List *old = stage.fighters;
	stage.fighters = filtered;
	ListFree(&old);
}

static void spawnEnemies(void) {
	stage.enemySpawnTimer -= 1;
	if (stage.enemySpawnTimer <= 0) {
		Entity *enemy = EntityAlloc();
		enemy->team = TeamPig;
		enemy->x = SCREEN_WIDTH;
		enemy->y = rand() % SCREEN_HEIGHT;
		enemy->texture = enemyTexture;

		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

		enemy->dx = -(2 + (rand() % 4));

		stage.enemySpawnTimer = 30 + (rand() % 60);

		ListAddItem(stage.fighters, enemy);
	}
}

static void fireBullet(void) {
	Entity *bullet = calloc(1, sizeof(Entity));

	bullet->x = player->x + player->w;
	bullet->y = player->y + ((int)(player->h / 2) - (int)(bullet->h / 2));
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

	List *old = stage.bullets;
	stage.bullets = filtered;
	ListFree(&old);
}

static void draw(void) {
	drawPlayer();
	drawBullets();
	drawFighters();
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

static void drawFighters(void) {
	ListForEach(stage.fighters, ^(void *ve) {
		Entity *e = ve;
		blit(e->texture, e->x, e->y);
	});
}
