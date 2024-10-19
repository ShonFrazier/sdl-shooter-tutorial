#include <stdlib.h>
#include "memory.h"

free_and_clear_block free_and_clear = ^(void **pp) {
  free(*pp);
  *pp = NULL;
};
