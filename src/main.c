/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include "common.h"
#include "draw.h"
#include "init.h"
#include "input.h"
#include "main.h"
#include "stage.h"

#define PLAYER_MOVE_DELTA 10
#define forever for(;;)
App   app;
Stage stage;

static void capFrameRate(long *then, float *remainder);

int main(int argc, char *argv[]) {
	long  then;
	float remainder;

	memset(&app, 0, sizeof(App));

	//initEntityPool();
	initSDL();
	initStage();
	atexit(cleanup);

	then = SDL_GetTicks();
	remainder = 0;

	forever {
		prepareScene();
		doInput();

		app.delegate.logic();
		app.delegate.draw();

		presentScene();
		capFrameRate(&then, &remainder);
	}

	return 0;
}

static void capFrameRate(long *then, float *remainder) {
	long wait = 16 + *remainder;
	wait = 16 + *remainder;
	*remainder -= (int)*remainder;

	long frameTime = SDL_GetTicks() - *then;
	wait -= frameTime;

	if (wait < 1) {
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;
	*then = SDL_GetTicks();
}
