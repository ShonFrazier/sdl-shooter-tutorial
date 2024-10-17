#include "list-test.h"
#include <stdlib.h>
#include <stdio.h>

//#define INT_HALF_BIT_COUNT ((sizeof(int)/2))
//#define INT_MAX ((~0 << INT_HALF_BIT_COUNT) >> 1)
//#define INT_MIN ( -(INT_MAX - 1) )

int INTMAX = 0;
int IntMax(void) {
  if (INTMAX == 0) {
    int p = 0;
    int c = 1;
    while (c>0) {
      p = c;
      c <<= 1;
      c += 1;
    }
    INTMAX = p;
  }

  return INTMAX;
}

int INTMIN = 0;
int IntMin(void) {
  if (INTMIN == 0) {
    INTMIN = -(IntMax() - 1);
  }

  return INTMIN;
}

void TestListAllocFree(CuTest *tc) {
  List *list = NULL;
  bool result = false;

  result = ListAlloc(&list, ListOptionsDefaults);

  CuAssertTrue(tc, result);
  CuAssertPtrNotNull(tc, list);

  result = ListFree(&list);

  CuAssertTrue(tc, result);
  CuAssertPtrIsNull(tc, list);

  result = ListAlloc(NULL, ListOptionsDefaults);

  CuAssertFalse(tc, result);
}

int int_cmp(const void *p1, const void *p2) {
  const int *i1 = p1;
  const int *i2 = p2;
  if (*i1 <  *i2) { return -1; }
  if (*i1 == *i2) { return  0; }
  if (*i1  > *i2) { return  1; }

  return IntMin();
}

// Just to make sure we don't futz with the above function too much
void TestIntComparator(CuTest *tc) {
  int result = 0;

  int i1 = IntMax();
  int i2 = IntMin();

  result = int_cmp(&i1, &i2);
  CuAssertIntEquals(tc, 1, result);

  i1 = 0, i2 = 0;
  result = int_cmp(&i1, &i2);
  CuAssertIntEquals(tc, 0, result);

  i1 = 1, i2 = 10;
  result = int_cmp(&i1, &i2);
  CuAssertIntEquals(tc, -1, result);
}

void TestListAdd(CuTest *tc) {
  List *list = NULL;
  bool result = false;

  // Test adding a specific number of items
  result = ListAlloc(&list, ListOptionsDefaults);

  int values[] = {5,4,3,2,1};

  for (int i=0; i<5; i+=1) {
    result = ListAddItem(list, &values[i]);
    CuAssertTrue(tc, result);
  }

  int count = 0;
  result = ListItemCount(list, &count);

  CuAssertTrue(tc, result);
  CuAssertIntEquals(tc, 5, count);

  // Make sure we can't add the same pointers
  for (int i=0; i<5; i+=1) {
    result = ListAddItem(list, &values[i]);
    CuAssertFalse(tc, result);
  }
  result = ListItemCount(list, &count);

  CuAssertTrue(tc, result);
  CuAssertIntEquals(tc, 5, count);


  result = ListFree(&list);
  CuAssertTrue(tc, result);
  CuAssertPtrIsNull(tc, list);

  // Test adding duplicate items
  int dup_values[] = {1,2,3,4,5,5,4,3,2,1};

  result = ListAlloc(&list, ListOptionUniqueItems);
  result = ListSetComparator(list, &int_cmp);
  for (int i=0; i<10; i+=1) {
    result = ListAddItem(list, &dup_values[i]);
    if (i < 5) {
      CuAssertTrue(tc, result);
    } else {
      CuAssertFalse(tc, result);
    }
  }

  result = ListItemCount(list, &count);
  CuAssertTrue(tc, result);
  CuAssertIntEquals(tc, 5, count);
}
