#include "app.h"

App *AppAlloc(void) {
  return calloc(1, sizeof(App));
}
