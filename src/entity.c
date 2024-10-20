#include <Block.h>
#include <SDL2/SDL.h>
#include "entity.h"
#include "util/collision.h"
#include "util/memory.h"

EntityPairCollisionTest collision_test = ^(Entity *e1, Entity *e2) {
  SDL_FRect r1 = {
    .x = (float)e1->x,
    .y = (float)e1->y,
    .w = (float)e1->w,
    .h = (float)e1->h,
  };

  SDL_FRect r2 = {
    .x = (float)e2->x,
    .y = (float)e2->y,
    .w = (float)e2->w,
    .h = (float)e2->h,
  };

  SDL_FRect inters;

  return (bool)SDL_IntersectFRect(&r1, &r2, &inters);
};

Entity *EntityAlloc(void) {
  Entity *entity = calloc(1, sizeof(Entity));
  entity->doesCollideWith = Block_copy(^(Entity *other) {
    if (entity == other) {
      return (bool)false;
    }
    return (bool)collision_test(entity, other);
  });

  return entity;
}

ImplFreeBlkType(Entity, Block_release((*pp)->doesCollideWith), {});
