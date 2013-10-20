#ifndef TEST_H
#define TEST_H

#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

typedef struct TestResult {
  struct TestResult *prev;
  struct TestResult *next;
  int value;
  char *name;
  char *file;
  int line;
} TestResult;

typedef TestResult* (*test_function)();
void _add_test(test_function t);
void run_tests();
void test_init();

#define add_test(name) _add_test(__test_##name)
#define TEST(fn_name) \
    TestResult * __test_##fn_name() { char *name = #fn_name;

#define TEST_RETURN(return_value) {               \
	TestResult *ret = malloc(sizeof(TestResult)); \
	memset(ret, 0, sizeof(TestResult));           \
	ret->line = __LINE__;                         \
                                                  \
	ret->file = malloc(strlen(__FILE__) + 1);     \
	strcpy(ret->file, __FILE__);                  \
                                                  \
	ret->name = malloc(strlen(name) + 1);         \
	strcpy(ret->name, name);                      \
                                                  \
    ret->prev = NULL;                             \
    ret->next = NULL;                             \
                                                  \
	ret->value = return_value;                    \
	                                              \
	return ret;                                   \
}

/* #define add_test(fn) _add_test(__test_##fn) */
#define pass() TEST_RETURN(EXIT_SUCCESS)
#define fail() TEST_RETURN(EXIT_FAILURE)

#endif
