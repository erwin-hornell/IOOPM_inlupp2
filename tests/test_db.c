#include <CUnit/Basic.h>
#include "../db.h"

void test_db_destroy()
{
    db_t *db = create_db();
    CU_ASSERT_PTR_NOT_NULL(db);
    destroy_db(db);
}

int main(void)
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite(
        "DB test",
        NULL,
        NULL);

    CU_add_test(suite, "create & destroy db", test_db_destroy);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}