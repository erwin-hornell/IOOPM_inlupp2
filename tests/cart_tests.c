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

void test_cart_add_one()
{
    cart_t *cart = cart_create();

    item_t *item = create_item("item", "an epic item", 99);
    cart_add(cart, item, 1);
    CU_ASSERT_TRUE(cart_amount(cart, item) == 1);

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



    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}