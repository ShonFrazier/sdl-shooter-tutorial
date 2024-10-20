/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include "app.h"
#include "common.h"
#include "draw.h"
#include "init.h"
#include "input.h"
#include "main.h"
#include "stage.h"
#include "util/util.h"

#define PLAYER_MOVE_DELTA 10
#define forever for(;;)

static void capFrameRate(long *then, float *remainder);

int main(int argc, char *argv[]) {
	long  then;
	float remainder;

	App *app = AppAlloc();
	initSDL(app);

	Stage *stage = StageAlloc(app);

	atexit(cleanup);

	then = SDL_GetTicks();
	remainder = 0;

	forever {
		prepareScene(app->renderer);
		doInput(app);

		app->delegate.logic();
		app->delegate.draw();

		presentScene(app->renderer);
		capFrameRate(&then, &remainder);
	}

	return 0;
}

static void capFrameRate(long *then, float *remainder) {
	long wait = 16 + *remainder;
	*remainder -= SDL_floorf(*remainder);

	long frameTime = SDL_GetTicks() - *then;
	wait -= frameTime;

	if (wait < 1) {
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;
	*then = SDL_GetTicks();
}
