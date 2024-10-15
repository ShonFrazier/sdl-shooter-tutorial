/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include "common.h"

#include "draw.h"
#include "init.h"
#include "input.h"
#include "main.h"

#define PLAYER_MOVE_DELTA 10
#define forever for(;;)

App    app;
Entity player;

int main(int argc, char *argv[])
{
	memset(&app, 0, sizeof(App));
	memset(&player, 0, sizeof(Entity));

	initSDL();

	atexit(cleanup);

	player.texture = loadTexture("gfx/player.png");
	player.x = 100;
	player.y = 100;

	forever {
		prepareScene();

		doInput();

		player.x += (app.delta.x * PLAYER_MOVE_DELTA);
		player.y += (app.delta.y * PLAYER_MOVE_DELTA);

		// printf("app.delta { x: %d , y: %d }\n", app.delta.x, app.delta.y);

		blit(player.texture, player.x, player.y);

		presentScene();

		SDL_Delay(16);
	}

	return 0;
}
