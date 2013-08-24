#include <tests.h>

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

void __run_test(TestResult* (*ptr)())
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

void run_tests()
{
  TestResult *failure;

	examples = failed = 0;
	failures = NULL;

  puts("\nBeginning tests.\n");

  __run_tests();

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
