#include <test.h>

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
		pass();

	test_setjmp_pt2(env, res);

	fail();
}

void test_setjmp_init() {
    // There's something wrong with this test. It jumps into nowhere. Disabled
    // for the time being.
    /* add_test(setjmp); */
}
