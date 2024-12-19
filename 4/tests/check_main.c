#include <check.h>
#include "../src/lib.h"
#include "../src/logger.h"

START_TEST(test_check_string)
{
    log_init("/tmp/aoc4.log", LOG_DEBUG);
    char test[] = "XMAS";
    ck_assert(check_string(test, 1, 3, 4) == false);
    ck_assert(check_string(test, 0, 1, 4) == true);
    char test2[] = "XMMMMMMMAAAASSSS";
    ck_assert(check_string(test2, 0, 4, 4) == true);
    ck_assert(check_string(test2, 0, 5, 4) == true);
    char test3[] = "XMMMMMMMAAAAASAM";
    ck_assert(check_string(test3, 0, -1, 4) == false);
    char test4[] = "XXXXMMMAAASASSSS";
    ck_assert(check_string(test4, 3, 3, 4) == true);
    ck_assert(check_string(test4, 1, 3, 4) == false); // This checks for crossing col boundary
    log_close();
}
END_TEST

Suite *main_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Main");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_check_string);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int fail_count;
    Suite *s;
    SRunner *sr;

    s = main_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    fail_count = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (fail_count == 0) ? 0 : 1;
}
