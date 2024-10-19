#include "entity.h"
#include "util/collision.h"
#include "util/memory.h"

EntityPairCollisionTest collision_test = ^(Entity *e1, Entity *e2) {
  return collision(e1->x, e1->y, e1->w, e1->h, e2->x, e2->y, e2->w, e2->h);
};

Entity *EntityAlloc(void) {
  Entity *entity = calloc(1, sizeof(Entity));
  entity->doesCollideWith = ^(Entity *other) {
    return (bool)collision_test(entity, other);
  };

  return entity;
}

ImplFreeBlkType(Entity);
