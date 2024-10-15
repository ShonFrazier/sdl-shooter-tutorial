/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include "common.h"

#include "draw.h"
#include "init.h"
#include "input.h"
#include "main.h"
#include "corgipaths.h"
#include "custom_events.h"

App    app;
Entity player;

#define forever for(;;)

int current_corgi = 0;

int main(int argc, char *argv[]) {
	memset(&app, 0, sizeof(App));
	memset(&player, 0, sizeof(Entity));


	initSDL();
	init_custom_events();

	player.x = 100;
	player.y = 100;
	player.texture = loadTexture("gfx/animals/corgis/x10/corgi-01.png");

	atexit(cleanup);

	forever {
		prepareScene();

		doInput();

		if (should_rotate_corgi()) {
			set_should_rotate_corgi(false);

			current_corgi += 1;
			current_corgi %= get_available_corgi_count();

			player.texture = loadTexture(get_corgi_path(current_corgi));
		}

		blit(player.texture, player.x, player.y);

		presentScene();

		SDL_Delay(16);
	}

	return 0;
}
