#include "collision.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_stdinc.h"
#include <stdbool.h>

#ifndef MAX
#define MAX(a,b) ((a)>=(b)) ? (a) : (b)
#endif
#ifndef MIN
#define MIN(a,b) ((a)<=(b)) ? (a) : (b)
#endif

bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
  return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}
