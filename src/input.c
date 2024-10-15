/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include "common.h"
#include "input.h"
#include "util/Object.h"

void process_keyup(const SDL_KeyboardEvent *event);

void doInput(void) {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYUP:
				printf("key up\n");
				process_keyup(&event.key);
				break;

			default:
				break;
		}
	}
}

bool _should_rotate_corgi = false;
bool should_rotate_corgi() {
	return _should_rotate_corgi;
}
void set_should_rotate_corgi(bool value) {
	_should_rotate_corgi = value;
}

Property(bool, should_keep_corgi);

void process_keyup(const SDL_KeyboardEvent *event) {
	printf("scancode: %d\n", event->keysym.scancode);
	if (event->keysym.scancode == SDL_SCANCODE_RETURN) {
		printf("Enter pressed\n");
		set_should_rotate_corgi(true);
	}
	if (event->keysym.scancode == SDL_SCANCODE_SPACE) {
		printf("Space pressed\n");
		set_should_keep_corgi(true);
	}
}
