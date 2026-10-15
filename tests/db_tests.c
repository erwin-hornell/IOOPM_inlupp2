#include <CUnit/Basic.h>
#include <string.h>
#include "../db.h"


// ---------------------------------------------------------
// Create / destroy
// ---------------------------------------------------------

void test_db_destroy()
{
    db_t *db = create_db();
    CU_ASSERT_PTR_NOT_NULL(db);
    destroy_db(db);
}

// ---------------------------------------------------------
// Add
// ---------------------------------------------------------

void test_db_add_once()
{
    db_t *db = create_db();
    char *name = "car";
    char *desc = "a red mazda";
    int price = 101;

    CU_ASSERT_TRUE(add_merch(db, name, desc, price));

    destroy_db(db);
}

void test_db_add_same()
{
    db_t *db = create_db();
    char *name = "car";
    char *desc = "a red mazda";
    int price = 101;

    CU_ASSERT_TRUE(add_merch(db, name, desc, price));
    CU_ASSERT_FALSE(add_merch(db, name, desc, price));

    destroy_db(db);
}

// ---------------------------------------------------------
// Remove
// ---------------------------------------------------------

void test_db_remove_empty()
{
    db_t *db = create_db();
    char *name = "car";

    CU_ASSERT_FALSE(remove_merch(db, name));

    destroy_db(db);
}

void test_db_remove_once()
{
    db_t *db = create_db();
    char *name = "car";
    char *desc = "a red mazda";
    int price = 101;

    CU_ASSERT_TRUE(add_merch(db, name, desc, price));
    CU_ASSERT_TRUE(remove_merch(db, name));

    destroy_db(db);
}

// ---------------------------------------------------------
// Update stock
// ---------------------------------------------------------

void test_db_update_stock()
{
    db_t *db = create_db();
    char *name = "car";
    char *desc = "a red mazda";
    int price = 101;
    char *loca = "20B";
    size_t amount = 20;
    size_t res = 0;

    CU_ASSERT_TRUE(add_merch(db, name, desc, price));
    CU_ASSERT_TRUE(add_stock(db, name, loca, amount));
    CU_ASSERT_TRUE(get_stock(db, name, &res));
    CU_ASSERT_EQUAL(amount, res);

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

    CU_add_test(suite, "adds 1 item", test_db_add_once);
    CU_add_test(suite, "adds the same item twice", test_db_add_same);

    CU_add_test(suite, "removes from empty db", test_db_remove_empty);
    CU_add_test(suite, "removes existing item", test_db_remove_once);

    CU_add_test(suite, "update stock once", test_db_update_stock);



    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}