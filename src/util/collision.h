#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpragma-once-outside-header"
#pragma once
#pragma clang diagnostic pop

#include <stdbool.h>
#include <SDL2/SDL.h>

bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
