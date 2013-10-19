#ifndef TEST_H
#define TEST_H

#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

static int examples = 0,
           failed   = 0;

typedef struct TestResult {
  struct TestResult *prev;
  struct TestResult *next;
  int value;
  char *name;
  char *file;
  int line;
} TestResult;

static TestResult *failures    = NULL,
                  *lastFailure = NULL;

#define TEST(fn_name) \
TestResult * __test_##fn_name() { char *name = #fn_name;

# define TEST_RETURN(return_value) {      \
	TestResult *ret = malloc(sizeof(TestResult)); \
	memset(ret, 0, sizeof(TestResult));  \
	ret->line = __LINE__;         \
                                \
	ret->file = malloc(strlen(name)); \
	strcpy(ret->file, __FILE__);  \
                                \
	ret->name = malloc(strlen(name));    \
	strcpy(ret->name, name);      \
                                \
  ret->prev = NULL;             \
  ret->next = NULL;             \
                                \
	ret->value = return_value;    \
	                              \
	return ret;                   \
}\
//define TEST

#define _(fn) __run_test(* __test_##fn)

#define test(args...) void __run_tests() { ( args ); }


void run_tests();

void __run_tests();
void __run_test(TestResult* (*ptr)());

#endif
