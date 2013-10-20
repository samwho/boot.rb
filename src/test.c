#include <test.h>
#include <test/setjmp.h>

static int examples = 0,
           failed   = 0,
           next_test = 0;

static test_function tests[1024];
static TestResult *failures    = NULL,
                  *lastFailure = NULL;

void _add_test(test_function t) {
    tests[next_test++] = t;
}

void test_init() {
    test_setjmp_init();
}

void run_tests() {
	TestResult *failure;

	examples = failed = 0;
	failures = NULL;

	puts("\nBeginning tests.\n");

    int i;
    for (i = 0; i < next_test; i++) {
        TestResult *t = tests[i]();
        examples++;

        if (t->value == EXIT_SUCCESS) {
            putc('.');
            free(t);
        } else {
            if (failures == NULL) {
                failures = lastFailure = t;
            } else {
                lastFailure->next = t;
                t->prev = lastFailure;
                lastFailure = t;
            }

            putc('F');
            failed++;
        }
    }

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
