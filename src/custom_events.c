#include "custom_events.h"
#include "dictionary.h"

Dictionary typesByName = NULL;
Dictionary typesByNumber = NULL;

ComparatorResult intp_cmp(const int *a, const int *b) {
  ComparatorResult result = OrderedSame;

  if (*a < *b) {
    result = OrderedAscending;
  }
  if (*a == *b) {
    result = OrderedSame;
  }
  if (*a > *b) {
    result = OrderedDescending;
  }

  return result;
}

int *intp_cpy(const int *a) {
  int *new = malloc(sizeof(int));
  *new = *a;
  return new;
}

const char SDL_EVENT_NAME_KEEP_CORGI[] = "KEEP_CORGI";
#define KEEP_CORGI "KEEP_CORGI"

const char *type_names[] = {
  SDL_EVENT_NAME_KEEP_CORGI,
  NULL
};

ComparatorResult keycmp(const void *k1, const void *k2) {
  return strcmp((char *)k1, (char *)k2);
}

void *keycpy(const void *k) {
  char *new = calloc(1, strlen(k)+1);
  strcpy(new, k);
  return new;
}

void init_custom_events(void) {
  typesByName = dictionary_alloc();
  dictionary_set_comparator(typesByName, keycmp);
  dictionary_set_key_copier(typesByName, keycpy);

  comparator cmp = &intp_cmp;
  copier cpy = &intp_cpy;

  typesByNumber = dictionary_alloc();
  dictionary_set_comparator(typesByNumber, cmp);
  dictionary_set_key_copier(typesByNumber, cpy);

  const char *type_name = type_names[0];
  for(int i = 1; type_name != NULL; i+=1) {
    printf("%s\n", type_name);
    int *id = NULL;
    id = malloc(sizeof(int));
    *id = SDL_RegisterEvents(1);
    dictionary_put(typesByName, type_name, id);
    dictionary_put(typesByNumber, id, type_name);

    type_name = type_names[i];
  }
}

bool strequal(char *s1, char *s2) {
  return strcmp(s1,s2) == 0;
}

void doCustomEvents(SDL_Event *event) {
  int id = event->type;
  char *name = (char *)dictionary_get(typesByNumber, &id);

  if (strequal(name, KEEP_CORGI)) {

  }
}
