#include <test.h>
#include <memory.h>

TEST(malloc)
    void* first  = malloc(64);
    void* second = malloc(64);

    if (first  == NULL)   fail("First malloc was NULL");
    if (second == NULL)   fail("Second malloc was NULL");
    if (first  == second) fail("First and second malloc returning same address");

    // Memory must be aligned on page boundaries.
    if ((unsigned int)first  % (BLOCK_MIN * 1024) != 0)
        fail("First malloc not page aligned");
    if ((unsigned int)second % (BLOCK_MIN * 1024) != 0)
        fail("Second malloc not page aligned");

    free(first);
    free(second);
}

void test_memory_init() {
    add_test(malloc);
}
