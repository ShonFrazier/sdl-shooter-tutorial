#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpragma-once-outside-header"
#pragma once
#pragma clang diagnostic pop

#include "util/util.h"
#include "app.h"

typedef struct {
  App *app;
	List *fighters;
	List *bullets;
	List *enemies;
	int enemySpawnTimer;
} Stage;

Stage *StageAlloc(App *);
