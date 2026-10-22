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

void test_cart_add_none()
{
    // create cart
    cart_t *cart = cart_create();

    CU_ASSERT_TRUE(cart_amount(cart, "car") == 0);

    cart_destroy(cart);
}

void test_cart_add_once()
{
    // create cart
    cart_t *cart = cart_create();

    // add merchandise to cart
    cart_add(cart, "car", 1);

    CU_ASSERT_TRUE(cart_amount(cart, "car") == 1);

    cart_destroy(cart);
}

void test_cart_add_once_two()
{
    // create cart
    cart_t *cart = cart_create();

    // add merchandise to cart
    cart_add(cart, "car", 2);

    CU_ASSERT_TRUE(cart_amount(cart, "car") == 2);

    cart_destroy(cart);
}

void test_cart_add_twice_same()
{
    // create cart
    cart_t *cart = cart_create();

    // add merchandise to cart
    cart_add(cart, "car", 1);
    cart_add(cart, "car", 1);

    CU_ASSERT_TRUE(cart_amount(cart, "car") == 2);

    cart_destroy(cart);
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
    CU_add_test(suite, "add no items to cart", test_cart_add_none);
    CU_add_test(suite, "add item to cart once", test_cart_add_once);
    CU_add_test(suite, "add item of quanity 2 to cart at once", test_cart_add_once_two);
    CU_add_test(suite, "add same item to cart twice", test_cart_add_twice_same);



    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}