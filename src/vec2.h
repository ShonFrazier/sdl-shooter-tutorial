typedef struct {
	int x;
	int y;
} Vec2;

Vec2 vec2_add_vec2(Vec2 v1, Vec2 v2);
Vec2 vec2_add_int (Vec2 v1, int i);
Vec2 vec2_sub_vec2(Vec2 v1, Vec2 v2);
Vec2 vec2_sub_int (Vec2 v1, int i);
Vec2 vec2_mul_vec2(Vec2 v1, Vec2 v2);
Vec2 vec2_mul_int (Vec2 v1, int i);

static const Vec2 DELTA_ZERO  = { .x= 0, .y= 0 };
static const Vec2 DELTA_ONE   = { .x= 1, .y= 1 };
static const Vec2 DELTA_NEG   = { .x=-1, .y=-1 };
static const Vec2 DELTA_UP    = { .x= 0, .y=-1 };
static const Vec2 DELTA_DOWN  = { .x= 0, .y= 1 };
static const Vec2 DELTA_LEFT  = { .x=-1, .y= 0 };
static const Vec2 DELTA_RIGHT = { .x= 1, .y= 0 };

typedef enum {
	DirectionNone = 0,
	DirectionEast = 1,
	DirectionNorthEast = 2,
	DirectionNorth = 3,
	DirectionNorthWest = 4,
	DirectionWest = 5,
	DirectionSouthWest = 6,
	DirectionSouth = 7,
	DirectionSouthEast = 8
} Direction;

static const Vec2 Directions[] = {
	{ .x= 0, .y= 0 },
	{ .x= 1, .y= 0 },
	{ .x= 1, .y=-1 },
	{ .x= 0, .y=-1 },
	{ .x=-1, .y=-1 },
	{ .x=-1, .y= 0 },
	{ .x=-1, .y= 1 },
	{ .x= 0, .y= 1 },
	{ .x= 1, .y= 1 },
};

Vec2 DirectionVector(Direction d);
