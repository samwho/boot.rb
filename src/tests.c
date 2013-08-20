#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <tests.h>

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

TestResult *failures    = NULL,
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
	strcpy(ret->name, name);     \
                                \
  ret->prev = NULL;             \
  ret->next = NULL;             \
                                \
	ret->value = return_value;    \
	                              \
	return ret;                   \
}\
//define TEST

void test_setjmp_pt2(jmp_buf env, int res)
{
	if (res != 0)
		res++;

	longjmp (env, res);
}

TEST(setjmp) //{
  jmp_buf env;
	int res = setjmp(env);

	if (res > 1)
		TEST_RETURN(EXIT_SUCCESS);

  test_setjmp_pt2(env, res);

	TEST_RETURN(EXIT_FAILURE);
}


void test_fail(TestResult *ret)
{
  if (failures == NULL) {
    failures = lastFailure = ret;
  } else {
    lastFailure->next = ret;
    ret->prev = lastFailure;
    lastFailure = ret;
  }

  putc('F');
  failed++;
}

void _test(TestResult* (*ptr)())
{
  TestResult *ret = ptr();

printf("0x%x\n", *(ret->name));
printf("0x%x\n", *(ret->file));

printf("%s\n", ret->name);
printf("%s\n", ret->file);
printf("%i\n", ret->line);

  examples++;

  if(ret->value != EXIT_SUCCESS)
    return test_fail(ret);

  putc('.');
}

#define test(fn) _test(* __test_##fn)

void run_tests()
{
  TestResult *failure;

	examples = failed = 0;
	failures = NULL;

  puts("\nBeginning tests.\n");

  test(setjmp);

  printf("\n\n%i examples, %i failed.\n\n", examples, failed);

  if (failed > 0) {
    puts("Failed examples:\n\n");

    failure = failures;

    do {
      printf("%s:%i %s", failure->file, failure->line, failure->name);
    } while ((failure = failure->next));

    puts("\n\n");
  }
}
