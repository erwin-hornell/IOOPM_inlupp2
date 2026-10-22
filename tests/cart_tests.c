#include <CUnit/Basic.h>
#include <string.h>
#include "../cart.h"


// ---------------------------------------------------------
// Create / destroy
// ---------------------------------------------------------

void test_cart_destroy()
{
    cart_t *cart = cart_create();
    CU_ASSERT_PTR_NOT_NULL_FATAL(cart);
    cart_destroy(cart);
}

// ---------------------------------------------------------
// Add wares
// ---------------------------------------------------------

void test_cart_add_once()
{
    cart_t *cart = cart_create();

    item_t *item = create_item("item", "an epic item", 99);
    cart_add(cart, item, 1);
    CU_ASSERT_EQUAL(cart_amount(cart, item), 1);

    cart_destroy(cart);
}

// ---------------------------------------------------------
// Remove
// ---------------------------------------------------------

void test_cart_remove_all()
{
    char *name = "car", *desc = "a fast car";
    size_t price = 99, amount = 1;

    cart_t *cart = cart_create();

    item_t *item = create_item(name, desc, price);
    cart_add(cart, item, amount);
    CU_ASSERT_EQUAL(cart_amount(cart, item), amount);
    cart_remove(cart, item, amount);
    CU_ASSERT_EQUAL(cart_amount(cart, item), 0);

    cart_destroy(cart);
}

void test_cart_remove_some()
{
    char *name = "car", *desc = "a fast car";
    size_t price = 99, amount = 2;

    cart_t *cart = cart_create();

    item_t *item = create_item(name, desc, price);
    cart_add(cart, item, amount);
    CU_ASSERT_EQUAL(cart_amount(cart, item), amount);
    cart_remove(cart, item, 1);
    CU_ASSERT_EQUAL(cart_amount(cart, item), 1);

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

    CU_add_test(suite, "create and destroy cart", test_cart_destroy);
    CU_add_test(suite, "add one merch to cart", test_cart_destroy);
    CU_add_test(suite, "remove all merch from cart", test_cart_remove_some);
    CU_add_test(suite, "remove some merch from cart", test_cart_remove_all);



    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}