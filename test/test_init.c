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
#include "utils.h"

static const char *const root = "/tmp/git_test";
static const char *const git_path = "/tmp/git_test/.git";
static const char *const head_path = "/tmp/git_test/.git/HEAD";
static const char *const objs_path = "/tmp/git_test/.git/objects";
static const char *const refs_path = "/tmp/git_test/.git/refs";

void cleanup() {
    rmrf(root);
}

void test_setup() {
    cleanup();
    mkdir(root, 0755);
    chdir(root);
}

static void test_init(void **state) {
    (void) state;
    test_setup();

    int res = init(NULL);

    assert_int_equal(res, 0);

    struct stat stat_buf;
    assert_int_equal(stat(git_path, &stat_buf), 0);
    assert_int_equal(stat(head_path, &stat_buf), 0);
    assert_int_equal(stat(objs_path, &stat_buf), 0);
    assert_int_equal(stat(refs_path, &stat_buf), 0);

    cleanup();
}

static void test_init_with_path(void **state) {
    (void) state;
    test_setup();

    int res = init("/tmp/git_test");

    assert_int_equal(res, 0);

    struct stat stat_buf;
    assert_int_equal(stat(head_path, &stat_buf), 0);
    assert_int_equal(stat(objs_path, &stat_buf), 0);
    assert_int_equal(stat(refs_path, &stat_buf), 0);

    cleanup();
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_init),
        cmocka_unit_test(test_init_with_path)
    };

    int res = cmocka_run_group_tests(tests, NULL, NULL);
    cleanup();
    return res;
}
