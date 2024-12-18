#include <check.h>
#include "../src/lib.h"

START_TEST(test_check_string)
{
    char test[] = "XMAS";
    ck_assert(check_string(test, 1, 3) == false);
    ck_assert(check_string(test, 0, 1) == true);
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
