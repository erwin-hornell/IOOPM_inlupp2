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
// Edit
// ---------------------------------------------------------

void test_db_edit_once()
{
    db_t *db = create_db();
    char *name = "car", *new_name = "mazda";
    char *desc = "a red mazda", *new_desc = "sick car";
    int price = 101, new_price = 202;

    CU_ASSERT_TRUE(add_merch(db, name, desc, price));
    CU_ASSERT_TRUE(edit_merch(db, name, new_name, new_desc, new_price));
    CU_ASSERT_FALSE(remove_merch(db, name));
    CU_ASSERT_TRUE(remove_merch(db, new_name));

    destroy_db(db);
}

void test_db_edit_exiting_name()
{
    db_t *db = create_db();
    char *name1 = "car", *name2 = "truck", *new_name = "mazda";
    char *desc1 = "a red mazda", *desc2 = "big thing", *new_desc = "sick car";
    int price1 = 101, price2 = 1001, new_price = 202;

    CU_ASSERT_TRUE(add_merch(db, name1, desc1, price1));
    CU_ASSERT_TRUE(add_merch(db, name2, desc2, price2));
    CU_ASSERT_FALSE(edit_merch(db, name1, name2, new_desc, new_price));
    CU_ASSERT_TRUE(remove_merch(db, name1));
    CU_ASSERT_FALSE(remove_merch(db, new_name));

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


// ---------------------------------------------------------
// Get all items
// ---------------------------------------------------------

void test_db_edit_exiting_name()
{
    db_t *db = create_db();
    char *names[] = {"item1", "item2", "item3", "item4", "item5", "item6"};
    char *desc[] = {"desc1", "desc2", "desc3", "desc4", "desc5", "desc6"};
    int price = 101;
    for(int i = 0; i < 6; i++)
    {
        CU_ASSERT_TRUE(add_merch(db, names[i], desc[i], price));
    }
    ioopm_list_t *items = get_all_items(db);
    
    ioopm_list_iterator_t *it;
    for(it = ioopm_list_iterator_create(items);
        !ioopm_list_iterator_at_end(it);
        ioopm_list_iterator_advance(it))
        {
            
        }
    ioopm_list_iterator_destroy(it);

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

    CU_add_test(suite, "edit item once", test_db_edit_once);
    CU_add_test(suite, "Try to edit merch to exiting name", test_db_edit_exiting_name);

    CU_add_test(suite, "update stock once", test_db_update_stock);



    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}