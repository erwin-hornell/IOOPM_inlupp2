#include <CUnit/Basic.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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

    ioopm_list_t *locs;
    CU_ASSERT_TRUE_FATAL(get_merch_locs(shop, "car", &locs));

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

    ioopm_list_t *locs;
    CU_ASSERT_TRUE_FATAL(get_merch_locs(shop, "car", &locs));

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
// Replenish db
// ---------------------------------------------------------
void test_replenish_db()
{
    shop_t *shop = shop_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(shop);

    ioopm_list_t *locs = ioopm_list_create();

    CU_ASSERT_FALSE_FATAL(get_merch_locs(shop, "car", &locs));
    CU_ASSERT_TRUE(ioopm_list_is_empty(locs));

    CU_ASSERT_TRUE(add_to_db(shop, "car", "A fast car", 99));

    ioopm_list_destroy(locs); // destroy empty list in locs before its updated and memory leaks

    CU_ASSERT_TRUE_FATAL(get_merch_locs(shop, "car", &locs));
    CU_ASSERT_TRUE(ioopm_list_is_empty(locs));

    CU_ASSERT_TRUE(db_replenish(shop, "car", "A01", 10));
    CU_ASSERT_TRUE(db_replenish(shop, "car", "B01", 5));
    CU_ASSERT_TRUE(db_replenish(shop, "car", "C10", 15));

    // note: added to A01 again => amount = 10 + 7 = 17
    CU_ASSERT_TRUE(db_replenish(shop, "car", "A01", 7));

    // iterate over locs, ensure correct amount
    CU_ASSERT_TRUE_FATAL(get_merch_locs(shop, "car", &locs));

    CU_ASSERT_PTR_NOT_NULL_FATAL(locs);
    CU_ASSERT_EQUAL(ioopm_list_size(locs), 3);

    const int expected[] = {17, 5, 15};

    size_t i = 0;
    ioopm_list_iterator_t *it;

    for (it = ioopm_list_iterator_create(locs); // create and iterate over iterator
        !ioopm_list_iterator_at_end(it);
        ioopm_list_iterator_advance(it))
    {
        shelf_t *loc = ioopm_list_iterator_current(it).p;

        CU_ASSERT_TRUE(i < 3);

        if (i < 3)
        {
            CU_ASSERT_EQUAL(shelf_amount(loc), expected[i]);
        }

        i++;
    }
    ioopm_list_iterator_destroy(it); // destroy iterator

    // try to replenish non-existant item
    CU_ASSERT_FALSE(db_replenish(shop, "truck", "A01", 1));

    CU_ASSERT_FALSE_FATAL(get_merch_locs(shop, "truck", &locs));

    shop_destroy(shop);
}

// ---------------------------------------------------------
// Add a cart
// ---------------------------------------------------------
void test_add_cart()
{
    shop_t *shop = shop_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(shop);

    new_cart(shop);
    new_cart(shop);
    new_cart(shop);

    shop_destroy(shop);
}

// ---------------------------------------------------------
// Remove a cart
// ---------------------------------------------------------
void test_remove_cart()
{
    shop_t *shop = shop_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(shop);

    CU_ASSERT_FALSE(remove_cart(shop, 0));
    new_cart(shop);
    new_cart(shop);
    CU_ASSERT_TRUE(remove_cart(shop, 0));
    CU_ASSERT_FALSE(remove_cart(shop, 0));
    CU_ASSERT_TRUE(remove_cart(shop, 1));

    shop_destroy(shop);
}

// ---------------------------------------------------------
// Add to cart
// ---------------------------------------------------------
void test_add_to_cart()
{
    shop_t *shop = shop_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(shop);

    new_cart(shop);
    new_cart(shop);
    // add stuff
    add_to_db(shop, "the item", "its the item", 100);
    CU_ASSERT_TRUE(add_to_cart(shop, 0, "the item", 2));
    CU_ASSERT_TRUE(add_to_cart(shop, 1, "the item", 99));
    // add it again
    CU_ASSERT_TRUE(add_to_cart(shop, 0, "the item", 3));

    shop_destroy(shop);
}

// ---------------------------------------------------------
// Remove from cart
// ---------------------------------------------------------
void test_remove_from_cart()
{
    shop_t *shop = shop_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(shop);

    add_to_db(shop, "item", "item the", 14);

    // remove invalid (no cart)
    CU_ASSERT_FALSE(remove_from_cart(shop, 0, "the item", 3));

    // remove valid
    new_cart(shop);
    CU_ASSERT_TRUE(add_to_cart(shop, 0, "item", 2));
    CU_ASSERT_TRUE(remove_from_cart(shop, 0, "item", 1));

    // remove invalid (cart 1 wrong amount)
    new_cart(shop);
    CU_ASSERT_FALSE(remove_from_cart(shop, 1, "item", 1));

    // remove invalid (removing more than is in the cart)
    new_cart(shop);
    CU_ASSERT_TRUE(add_to_cart(shop, 2, "item", 1));
    CU_ASSERT_FALSE(remove_from_cart(shop, 2, "item", 2));

    shop_destroy(shop);
}

// ---------------------------------------------------------
// Get all cart items
// ---------------------------------------------------------
void test_list_cart()
{
    shop_t *shop = shop_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(shop);

    // no cart
    ioopm_list_t *items;
    CU_ASSERT_FALSE_FATAL(cart_get_all_items(shop, 0, &items));

    // empty cart
    new_cart(shop);
    CU_ASSERT_TRUE_FATAL(cart_get_all_items(shop, 0, &items));
    CU_ASSERT_TRUE(ioopm_list_is_empty(items));
    ioopm_list_destroy(items);

    // add one to cart
    add_to_db(shop, "car", "goes fast", 10000);

    CU_ASSERT_TRUE(add_to_cart(shop, 0, "car", 1));
    CU_ASSERT_TRUE_FATAL(cart_get_all_items(shop, 0, &items));

    item_t *item_from_list = ioopm_list_head(items).p;
    CU_ASSERT_STRING_EQUAL(item_name(item_from_list), "car");
    ioopm_list_destroy(items);

    // TOFIX: add multiple to cart

    shop_destroy(shop);
}

// ---------------------------------------------------------
// Checkout
// ---------------------------------------------------------
void test_shop_checkout_empty()
{
    shop_t *shop = shop_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(shop);

    new_cart(shop);
    CU_ASSERT_TRUE(checkout_cart(shop, 0));

    shop_destroy(shop);
}

void test_shop_checkout_valid()
{
    shop_t *shop = shop_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(shop);

    // add items to shop database
    add_to_db(shop, "pc", "you can game", 2000);

    db_replenish(shop, "pc", "A01", 4);

    // add items to carts
    new_cart(shop);
    new_cart(shop);

    add_to_cart(shop, 0, "pc", 2);
    add_to_cart(shop, 1, "pc", 2);

    // checkout carts
    CU_ASSERT_TRUE(checkout_cart(shop, 0)); // MEMORY ERROR: Use of uninitialised value of size 8
    CU_ASSERT_TRUE(checkout_cart(shop, 1)); // MEMORY ERROR: Use of uninitialised value of size 8

    shop_destroy(shop);
}

void test_shop_checkout_invalid()
{
    shop_t *shop = shop_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(shop);

    // add items to shop database
    add_to_db(shop, "pc", "you can game", 2000);

    db_replenish(shop, "pc", "A01", 3);

    // create carts and add items
    new_cart(shop);
    new_cart(shop);

    add_to_cart(shop, 0, "pc", 2);
    add_to_cart(shop, 1, "pc", 2);

    // checkout carts
    CU_ASSERT_TRUE(checkout_cart(shop, 0));
    CU_ASSERT_FALSE(checkout_cart(shop, 1));

    shop_destroy(shop);
}

// ---------------------------------------------------------
// Main
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

    CU_add_test(suite, "Replenish stock", test_replenish_db);

    CU_add_test(suite, "add carts to shop", test_add_cart);

    CU_add_test(suite, "remove carts from shop", test_remove_cart);

    CU_add_test(suite, "add to cart", test_add_to_cart);

    CU_add_test(suite, "remove from cart", test_remove_from_cart);

    CU_add_test(suite, "get carts' content lists", test_list_cart);

    CU_add_test(suite, "empty checkout", test_shop_checkout_empty);

    CU_add_test(suite, "valid checkout", test_shop_checkout_valid);

    CU_add_test(suite, "invalid checkout", test_shop_checkout_invalid);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}