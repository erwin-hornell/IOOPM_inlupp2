#include <CUnit/Basic.h>
#include <string.h>
#include <stdio.h>
#include "../shop.h"
#include "../generics/generics.h"


// ---------------------------------------------------------
// Create / destroy
// ---------------------------------------------------------

void test_shop_destroy()
{
    shop_t *shop = shop_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(shop);
    shop_destroy(shop);

}

// ---------------------------------------------------------
// Add merch to db
// ---------------------------------------------------------

void test_shop_add_merch_once()
{
    char *name = "car", *desc = "a fast car";
    size_t price = 99;
    shop_t *shop = shop_create();
    CU_ASSERT_TRUE(add_to_db(shop, name, desc, price));

    shop_destroy(shop);

}

void test_shop_add_existing()
{
    char *name = "car", *desc = "a fast car";
    size_t price = 99;
    shop_t *shop = shop_create();
    CU_ASSERT_TRUE(add_to_db(shop, name, desc, price));
    CU_ASSERT_FALSE(add_to_db(shop, name, desc, price));

    shop_destroy(shop);

}

// ---------------------------------------------------------
// Remove merch from db
// ---------------------------------------------------------

void test_shop_remove_once()
{
    char *name = "car", *desc = "a fast car";
    size_t price = 99;
    shop_t *shop = shop_create();
    CU_ASSERT_TRUE(add_to_db(shop, name, desc, price));
    CU_ASSERT_TRUE(remove_from_db(shop, name));

    shop_destroy(shop);

}

void test_shop_remove_twice()
{
    char *name1 = "car", *desc1 = "a fast car";
    char *name2 = "truck", *desc2 = "a big truck";
    size_t price = 99;
    shop_t *shop = shop_create();
    CU_ASSERT_TRUE(add_to_db(shop, name1, desc1, price));
    CU_ASSERT_TRUE(add_to_db(shop, name2, desc2, price));
    CU_ASSERT_TRUE(remove_from_db(shop, name1));
    CU_ASSERT_FALSE(remove_from_db(shop, name1));
    shop_destroy(shop);

}

// ---------------------------------------------------------
// Edit merch in db
// ---------------------------------------------------------

void test_shop_edit_once()
{
    char *name = "car", *desc = "a fast car";
    char *new_name = "truck", *new_desc = "a large truck";
    size_t price = 99;
    shop_t *shop = shop_create();
    CU_ASSERT_TRUE(add_to_db(shop, name, desc, price));
    CU_ASSERT_TRUE(edit_item(shop, name, new_name, new_desc, price));
    CU_ASSERT_FALSE(remove_from_db(shop, name));

    shop_destroy(shop);
}


// ---------------------------------------------------------
// List db
// ---------------------------------------------------------

void test_shop_list_db_alphabetical_order(void)
{
    shop_t *shop = shop_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(shop);

    // Add items deliberately out of alphabetical order.
    CU_ASSERT_TRUE(add_to_db(shop, "truck", "A big truck", 199));
    CU_ASSERT_TRUE(add_to_db(shop, "car", "A fast car", 99));
    CU_ASSERT_TRUE(add_to_db(shop, "bike", "A bicycle", 49));
    CU_ASSERT_TRUE(add_to_db(shop, "plane", "An aircraft", 299));

    ioopm_list_t *items = list_db(shop);
    CU_ASSERT_PTR_NOT_NULL_FATAL(items);

    const char *expected[] = {
        "bike",
        "car",
        "plane",
        "truck"
    };

    CU_ASSERT_EQUAL(ioopm_list_size(items), 4);

    ioopm_list_iterator_t *it;

    size_t i = 0;

    for (it = ioopm_list_iterator_create(items);
        !ioopm_list_iterator_at_end(it);
        ioopm_list_iterator_advance(it))
    {
        item_t *item = ioopm_list_iterator_current(it).p;

        CU_ASSERT_TRUE(i < 4);

        if (i < 4)
        {
            CU_ASSERT_STRING_EQUAL(item_name(item), expected[i]);
        }

        i++;
    }

    CU_ASSERT_EQUAL(i, 4);

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(items);
    shop_destroy(shop);
}

// ---------------------------------------------------------
// List locations
// ---------------------------------------------------------

void test_shop_get_merch_locs_empty(void)
{
    shop_t *shop = shop_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(shop);

    CU_ASSERT_TRUE(add_to_db(shop, "car", "A fast car", 99));

    ioopm_list_t *locs = get_merch_locs(shop, "car");

    CU_ASSERT_PTR_NOT_NULL_FATAL(locs);
    CU_ASSERT_TRUE(ioopm_list_is_empty(locs));
    shop_destroy(shop);
}


void test_shop_get_merch_locs(void)
{
    shop_t *shop = shop_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(shop);

    CU_ASSERT_TRUE(add_to_db(shop, "car", "A fast car", 99));

    CU_ASSERT_TRUE(db_replenish(shop, "car", "A01", 10));
    CU_ASSERT_TRUE(db_replenish(shop, "car", "B01", 5));
    CU_ASSERT_TRUE(db_replenish(shop, "car", "C10", 15));

    ioopm_list_t *locs = get_merch_locs(shop, "car");

    CU_ASSERT_PTR_NOT_NULL_FATAL(locs);
    CU_ASSERT_EQUAL(ioopm_list_size(locs), 3);

    


    const char *expected[] = {"A01", "B01", "C10"};
    size_t i = 0;
    ioopm_list_iterator_t *it;
    for (it = ioopm_list_iterator_create(locs);
        !ioopm_list_iterator_at_end(it);
        ioopm_list_iterator_advance(it))
    {
        shelf_t *loc = ioopm_list_iterator_current(it).p;

        CU_ASSERT_TRUE(i < 3);

        if (i < 3)
        {
            CU_ASSERT_STRING_EQUAL(shelf_name(loc), expected[i]);
        }

        i++;
    }

    CU_ASSERT_EQUAL(i, 3);

    ioopm_list_iterator_destroy(it);
    shop_destroy(shop);
}

// ---------------------------------------------------------
// Replanish db
// ---------------------------------------------------------

// ---------------------------------------------------------
// Add cart
// ---------------------------------------------------------

// ---------------------------------------------------------
// Remove cart
// ---------------------------------------------------------

// ---------------------------------------------------------
// Add to cart
// ---------------------------------------------------------

// ---------------------------------------------------------
// Remove from cart
// ---------------------------------------------------------

// ---------------------------------------------------------
// List cart items
// ---------------------------------------------------------

// ---------------------------------------------------------
// Remove cart
// ---------------------------------------------------------

// ---------------------------------------------------------
// Checkout
// ---------------------------------------------------------


int main(void)
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite(
        "DB test",
        NULL,
        NULL);

    CU_add_test(suite, "Create & destroy shop", test_shop_destroy);

    CU_add_test(suite, "Add item to db once", test_shop_add_merch_once);
    CU_add_test(suite, "Add existing itemto db", test_shop_add_existing);

    CU_add_test(suite, "Remove item once", test_shop_remove_once);
    CU_add_test(suite, "Remove the same item twice", test_shop_remove_twice);

    CU_add_test(suite, "Edits an item once", test_shop_edit_once);

    CU_add_test(suite, "List database alphabetically", test_shop_list_db_alphabetical_order);

    CU_add_test(suite, "Get empty merchandise locations", test_shop_get_merch_locs_empty);

    CU_add_test(suite, "Get merchandise locations", test_shop_get_merch_locs);



    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}