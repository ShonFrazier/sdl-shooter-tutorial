#pragma once

/*
typedef struct Any {
    enum {
      typeUndefined,
      typeInt,
      typeUint,
      typeString,
      typeByteString,
      typeLong,
      typeFloat,
      typeDouble,
    } type;

    union {
        int i;
        unsigned int u;
        char* s;
        long l;
        float f;
        double d;
    } value;
} Any;

typedef void *(*object_alloc_f)();
typedef void *(^object_alloc_b)();
typedef union {
  object_alloc_f f;
  object_alloc_b b;
} object_alloc;

typedef void (*object_free_f)();
typedef void (^object_free_b)();
typedef union {
  object_free_f f;
  object_free_b b;
} object_free;

typedef void(*object_set_field_f)(Any val);
typedef void(^object_set_field_b)(Any val);
typedef union {
  object_set_field_f f;
  object_set_field_b b;
} object_set_field;

typedef Any *(*object_get_field_f)();
typedef Any *(^object_get_field_b)();
typedef union {
  object_get_field_f f;
  object_get_field_b b;
} object_get_field;

typedef void(*object_set_indexed_f)(int, Any);
typedef void(^object_set_indexed_b)(int, Any);
typedef union {
  object_set_indexed_f f;
  object_set_indexed_b b;
} object_set_indexed;

typedef Any *(*object_get_indexed_f)(int);
typedef Any *(^object_get_indexed_b)(int);
typedef union {
  object_get_indexed_f f;
  object_get_indexed_b b;
} object_get_indexed;
*/

#define Property(T,NAME) \
  static T _ ## NAME; \
  T get_ ## NAME() { \
    return _ ## NAME; \
  } \
  void set_ ## NAME(T value) { \
    _ ## NAME = value; \
  }

