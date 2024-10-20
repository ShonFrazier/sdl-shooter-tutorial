#include "common.h"
#include "input.h"
#include "app.h"


static void doKeyUp(App *app, SDL_KeyboardEvent *event) {
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
		app->keyboard[event->keysym.scancode] = 0;
	}
}

static void doKeyDown(App *app, SDL_KeyboardEvent *event) {
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
		app->keyboard[event->keysym.scancode] = 1;
	}
}

void doInput(App *app) {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				doKeyDown(app, &event.key);
				break;

			case SDL_KEYUP:
				doKeyUp(app, &event.key);
				break;

			default:
				break;
		}
	}
}
