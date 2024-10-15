#include "structs.h"

Vec2 vec2_add(Vec2 v1, Vec2 v2) {
  Vec2 new = { .x = v1.x + v2.x, .y = v1.y + v2.y };
  return new;
}

Vec2 vec2_multiply(Vec2 v1, Vec2 v2) {
  Vec2 new = { .x = v1.x * v2.x, .y = v1.y * v2.y };
  return new;
}
