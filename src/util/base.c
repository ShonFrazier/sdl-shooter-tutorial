#include <stdlib.h>
#include <Block.h>
#include "base.h"

VoidVoidBlock EmptyCleanup = ^(){};

Base *BaseAlloc(void) {
  Base *base = calloc(1, sizeof(Base));
  base->cleanup = EmptyCleanup;

  return base;
}

void BaseInit(Base *base, VoidVoidBlock cleanup) {
  base->cleanup = Block_copy(cleanup);
}
