#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "init.h"

static const char *const head_path = "/tmp/git_test/HEAD";
static const char *const objs_path = "/tmp/git_test/objects/";
static const char *const refs_path = "/tmp/git_test/refs/";

void cleanup_test() {
    remove(head_path);
    rmdir(objs_path);
    rmdir(refs_path);
}

static void test_init(void **state) {
    (void) state;

    int res = init("/tmp/git_test");

    assert_int_equal(res, 0);

    struct stat stat_buf;
    assert_int_equal(stat(head_path, &stat_buf), 0);
    assert_int_equal(stat(objs_path, &stat_buf), 0);
    assert_int_equal(stat(refs_path, &stat_buf), 0);

    cleanup_test();
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_init)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
