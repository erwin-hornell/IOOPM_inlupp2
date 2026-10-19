#include <CUnit/Basic.h>
#include <string.h>
#include "../cart.h"


// ---------------------------------------------------------
// Create / destroy
// ---------------------------------------------------------

void test_cart_destroy()
{
    cart_t *cart = cart_create();
    CU_ASSERT_PTR_NOT_NULL(cart);
    cart_destroy(cart);
}

// ---------------------------------------------------------
// Add
// ---------------------------------------------------------

void test_cart_add_once()
{
    // create database
    db_t *db = create_db();
    char *name = "car";
    char *desc = "a red mazda";
    int price = 101;

    // add merchandise to database
    add_merch(db, name, desc, price);

    // create cart
    cart_t *cart = cart_create();

    // add merchandise to cart
    CU_ASSERT_TRUE(cart_add(cart, db, "car", 1));

    // TODO: check precisely 1 of ware is in cart

    cart_destroy(cart);
    destroy_db(db);
}

void test_cart_add_once_two()
{
    // create database
    db_t *db = create_db();
    char *name = "car";
    char *desc = "a red mazda";
    int price = 101;

    // add merchandise to database
    add_merch(db, name, desc, price);

    // create cart
    cart_t *cart = cart_create();

    // add merchandise to cart
    CU_ASSERT_TRUE(cart_add(cart, db, "car", 2));

    // TODO: check precisely 2 of ware is in cart

    cart_destroy(cart);
    destroy_db(db);
}

void test_cart_add_twice_same()
{
    // create database
    db_t *db = create_db();
    char *name = "car";
    char *desc = "a red mazda";
    int price = 101;

    // add merchandise to database
    add_merch(db, name, desc, price);

    // create cart
    cart_t *cart = cart_create();

    // add merchandise to cart
    CU_ASSERT_TRUE(cart_add(cart, db, "car", 1));
    CU_ASSERT_TRUE(cart_add(cart, db, "car", 1));

    // TODO: check precisely 2 of ware is in cart

    destroy_db(db);
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

    CU_add_test(suite, "create & destroy cart", test_cart_destroy);
    CU_add_test(suite, "add item to cart once", test_cart_add_once);
    CU_add_test(suite, "add item of quanity 2 to cart at once", test_cart_add_once_two);
    CU_add_test(suite, "add same item to cart twice", test_cart_add_twice_same);



    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}