/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include "common.h"
#include "input.h"

extern App app;

static void doKeyUp(SDL_KeyboardEvent *event) {
	if (event->repeat == 0) {
		if (event->keysym.scancode == SDL_SCANCODE_UP) {
			app.delta = vec2_sub_vec2(app.delta, DELTA_UP);
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
			app.delta = vec2_sub_vec2(app.delta, DELTA_DOWN);
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
			app.delta = vec2_sub_vec2(app.delta, DELTA_LEFT);
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
			app.delta = vec2_sub_vec2(app.delta, DELTA_RIGHT);
		if (event->keysym.scancode == SDL_SCANCODE_LCTRL)
		{
			app.fire = 0;
		}
	}
}

static void doKeyDown(SDL_KeyboardEvent *event) {
	if (event->repeat == 0) {
		if (event->keysym.scancode == SDL_SCANCODE_UP) {
			app.delta = vec2_add_vec2(app.delta, DELTA_UP);
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
			app.delta = vec2_add_vec2(app.delta, DELTA_DOWN);
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
			app.delta = vec2_add_vec2(app.delta, DELTA_LEFT);
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
			app.delta = vec2_add_vec2(app.delta, DELTA_RIGHT);

		if (event->keysym.scancode == SDL_SCANCODE_LCTRL)
		{
			app.fire = 1;
		}
	}
}

void doInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				doKeyDown(&event.key);
				break;

			case SDL_KEYUP:
				doKeyUp(&event.key);
				break;

			default:
				break;
		}
	}
}
