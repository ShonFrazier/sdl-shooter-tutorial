#include "structs.h"
#include "stdbool.h"

Vec2 vec2_add_vec2(Vec2 v1, Vec2 v2) {
  Vec2 new = { .x = v1.x + v2.x, .y = v1.y + v2.y };
  return new;
}

Vec2 vec2_add_int(Vec2 v, int i) {
  Vec2 new = { .x = v.x + i, .y = v.y + i };
  return new;
}

Vec2 vec2_mul_vec2(Vec2 v1, Vec2 v2) {
  Vec2 new = { .x = v1.x * v2.x, .y = v1.y * v2.y };
  return new;
}

Vec2 vec2_mul_int (Vec2 v, int i) {
  Vec2 new = { .x = v.x * i, .y = v.x * i };
  return new;
}

Vec2 vec2_sub_vec2(Vec2 v1, Vec2 v2) {
  Vec2 new = { .x = v1.x - v2.x, .y = v1.y - v2.y };
  return new;
}

Vec2 vec2_sub_int (Vec2 v, int i) {
  Vec2 new = { .x = v.x - i, .y = v.y - i };
  return new;
}

Vec2 DirectionVector(Direction d) {
	return Directions[d];
}

#define Log(M) printf("%s %d %s: %s\n", __FILE__, __LINE__, __FUNCTION__, M);
#define Logf(F, ...) { \
  int len = strlen(F) * 2; \
  char *ff = calloc(1, len+1); \
  sprintf(ff, F, __VA_ARGS__); \
  Log(ff); \
}

struct EntityPool {
  int count;
  Entity *first;
};

void *my_calloc(int count, size_t size) {
  Log("Entered");
  Logf("  count %d  size %zu", count, size);
  void *p = calloc(count, size);
  Logf("  pointer: %p", p);

  Log("Return");
  return p;
}

void *my_realloc(void *p, size_t size) {
  Log("Entered");
  Logf("  old %p  size %zu", p, size);
  void *re = realloc(p, size);
  Logf("  new %p", re);

  Log("Return");
  return re;
}

static struct EntityPool *_pool = NULL;
void initEntityPool() {
  Log("enter");
  int initialCount = 2;

  if (_pool == NULL) {
    Log("alloc EntityPool");
    _pool = my_calloc(1, sizeof(struct EntityPool));
  }

  if (_pool->first == NULL) {
    Log("allocating 2 entities");
    _pool->count = initialCount;
    _pool->first = my_calloc(initialCount, sizeof(struct Entity));

    Entity *e = _pool->first;
    for(int i=0; i<initialCount; i+=1 ) {
      e->fromPool = true;
      e++;
    }
  }

  Log("exit");
}


Entity *EntityAlloc() {
  Log("Entered");

  if (_pool == NULL) {
    Log("No pool");
    return NULL;
  }

  if (_pool->first == NULL) {
    Log("No entities in pool");
    return NULL;
  }

  Entity *e = _pool->first;
  bool found = false;
  for (int i = 0; i < _pool->count; i += 1) {
    if (e->used) {
      Log("skip");
      e++;
      continue;
    } else {
      found = true;
      Log("Found, returning existing")
      e->used = true;
      return e;
    }
  }

  int newCount = _pool->count * 2;
  Log("Not found, creating new");

  char *count_msg = my_calloc(1, 100);
  sprintf(count_msg, " %d entries", _pool->count * 2);

  Log(count_msg); free(count_msg);

  void *current = _pool->first;
  void *copyOfExisting = my_realloc(current, _pool->count * 2 * sizeof(Entity));
  void *new = copyOfExisting + _pool->count;
  memset(new, 0, _pool->count);

  if (copyOfExisting == NULL) {
    return NULL;
  }

  _pool->first = copyOfExisting;
  _pool->count *= 2;

  Entity *newEntity = new;
  newEntity->fromPool = true;
  newEntity->used = true;

  Log("Returning new");
  return newEntity;
}

void EntityFree(Entity *e) {
  if (e->fromPool) {
    e->used = false;
  } else {
    free(e);
  }
}

void clearAndFree(void *p, int size) {
  if (size != 0) {
    memset(p, 0, size);
  }
  free(p);
}
