#include <stdio.h>
#include "CuTest.h"
#include "list-test.h"

CuSuite* SetupSuite(void) {
  CuSuite *suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, TestIntComparator);
  SUITE_ADD_TEST(suite, TestListAllocFree);
  SUITE_ADD_TEST(suite, TestListAdd);

  return suite;
}

void RunTests(void) {
  CuString* output = CuStringNew();
  CuSuite* suite = SetupSuite();

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);
}

int main(void)
{
  RunTests();
  return 0;
}
