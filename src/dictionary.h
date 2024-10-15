#pragma once

typedef struct Tree_s *Dictionary;

typedef enum ComparatorResult_e {
  OrderedAscending = -1,
  OrderedSame = 0,
  OrderedDescending = 1
} ComparatorResult;
typedef ComparatorResult (*comparator)(const void *, const void *);
typedef void *(*copier)(const void *);


Dictionary dictionary_alloc(void);
void dictionary_free(Dictionary *);
const void *dictionary_put(Dictionary, const void *key, const void *value);
const void *dictionary_get(Dictionary, const void *key);

void dictionary_set_comparator(Dictionary d, comparator cmp);
void dictionary_set_key_copier(Dictionary d, copier cpy);

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
