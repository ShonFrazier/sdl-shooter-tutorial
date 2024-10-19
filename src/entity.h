#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpragma-once-outside-header"
#pragma once
#pragma clang diagnostic pop

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "util/memory.h"
#include "defs.h"

typedef struct Entity Entity;

typedef bool (^EntityPairCollisionTest)(Entity *, Entity *);
typedef bool (^EntitySelfCollisionTest)(Entity *);

struct Entity {
  float x;
  float y;
  int w;
  int h;
  float dx;
  float dy;
  int health;
  int reload;
  TeamSide team;
  SDL_Texture *texture;
  EntitySelfCollisionTest doesCollideWith;
};

Entity *EntityAlloc(void);
DeclFreeBlkType(Entity);
