#include "vec2.h"

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
