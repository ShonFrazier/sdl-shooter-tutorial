#include <stddef.h>

int get_available_corgi_count(void) {
  return 74;
}

char *corgis[74] = {
  "gfx/animals/corgis/x10/corgi-01.png", "gfx/animals/corgis/x10/corgi-02.png",
  "gfx/animals/corgis/x10/corgi-03.png", "gfx/animals/corgis/x10/corgi-04.png",
  "gfx/animals/corgis/x10/corgi-05.png", "gfx/animals/corgis/x10/corgi-06.png",
  "gfx/animals/corgis/x10/corgi-07.png", "gfx/animals/corgis/x10/corgi-08.png",
  "gfx/animals/corgis/x10/corgi-09.png", "gfx/animals/corgis/x10/corgi-10.png",
  "gfx/animals/corgis/x10/corgi-11.png", "gfx/animals/corgis/x10/corgi-12.png",
  "gfx/animals/corgis/x10/corgi-13.png", "gfx/animals/corgis/x10/corgi-14.png",
  "gfx/animals/corgis/x10/corgi-15.png", "gfx/animals/corgis/x10/corgi-16.png",
  "gfx/animals/corgis/x10/corgi-17.png", "gfx/animals/corgis/x10/corgi-18.png",
  "gfx/animals/corgis/x10/corgi-19.png", "gfx/animals/corgis/x10/corgi-20.png",
  "gfx/animals/corgis/x10/corgi-21.png", "gfx/animals/corgis/x10/corgi-22.png",
  "gfx/animals/corgis/x10/corgi-23.png", "gfx/animals/corgis/x10/corgi-24.png",
  "gfx/animals/corgis/x10/corgi-25.png", "gfx/animals/corgis/x10/corgi-26.png",
  "gfx/animals/corgis/x10/corgi-27.png", "gfx/animals/corgis/x10/corgi-28.png",
  "gfx/animals/corgis/x10/corgi-29.png", "gfx/animals/corgis/x10/corgi-30.png",
  "gfx/animals/corgis/x10/corgi-31.png", "gfx/animals/corgis/x10/corgi-32.png",
  "gfx/animals/corgis/x10/corgi-33.png", "gfx/animals/corgis/x10/corgi-34.png",
  "gfx/animals/corgis/x10/corgi-35.png", "gfx/animals/corgis/x10/corgi-36.png",
  "gfx/animals/corgis/x10/corgi-37.png", "gfx/animals/corgis/x10/corgi-38.png",
  "gfx/animals/corgis/x10/corgi-39.png", "gfx/animals/corgis/x10/corgi-40.png",
  "gfx/animals/corgis/x10/corgi-41.png", "gfx/animals/corgis/x10/corgi-42.png",
  "gfx/animals/corgis/x10/corgi-43.png", "gfx/animals/corgis/x10/corgi-44.png",
  "gfx/animals/corgis/x10/corgi-45.png", "gfx/animals/corgis/x10/corgi-46.png",
  "gfx/animals/corgis/x10/corgi-47.png", "gfx/animals/corgis/x10/corgi-48.png",
  "gfx/animals/corgis/x10/corgi-49.png", "gfx/animals/corgis/x10/corgi-50.png",
  "gfx/animals/corgis/x10/corgi-51.png", "gfx/animals/corgis/x10/corgi-52.png",
  "gfx/animals/corgis/x10/corgi-53.png", "gfx/animals/corgis/x10/corgi-54.png",
  "gfx/animals/corgis/x10/corgi-55.png", "gfx/animals/corgis/x10/corgi-56.png",
  "gfx/animals/corgis/x10/corgi-57.png", "gfx/animals/corgis/x10/corgi-58.png",
  "gfx/animals/corgis/x10/corgi-59.png", "gfx/animals/corgis/x10/corgi-60.png",
  "gfx/animals/corgis/x10/corgi-61.png", "gfx/animals/corgis/x10/corgi-62.png",
  "gfx/animals/corgis/x10/corgi-63.png", "gfx/animals/corgis/x10/corgi-64.png",
  "gfx/animals/corgis/x10/corgi-65.png", "gfx/animals/corgis/x10/corgi-66.png",
  "gfx/animals/corgis/x10/corgi-67.png", "gfx/animals/corgis/x10/corgi-68.png",
  "gfx/animals/corgis/x10/corgi-69.png", "gfx/animals/corgis/x10/corgi-70.png",
  "gfx/animals/corgis/x10/corgi-71.png", "gfx/animals/corgis/x10/corgi-72.png",
  "gfx/animals/corgis/x10/corgi-73.png", "gfx/animals/corgis/x10/corgi-74.png",
};

const char *get_corgi_path(int index) {
  return corgis[index];
}
