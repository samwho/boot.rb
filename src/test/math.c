#include <test.h>
#include <math.h>

TEST(abs)
    if (abs(-1) == 1) {
        pass();
    } else {
        fail(NULL);
    }
}

void test_math_init() {
    add_test(abs);
}
