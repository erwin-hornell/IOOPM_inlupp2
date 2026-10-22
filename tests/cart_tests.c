#include <CUnit/Basic.h>
#include <string.h>
#include <stdio.h>
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
    char *name = "car", *desc = "a fast car";
    size_t price = 99, amount = 1; 

    cart_t *cart = cart_create();

    item_t *item = create_item(name, desc, price);
    cart_add(cart, item, amount);
    CU_ASSERT_EQUAL(cart_amount(cart, item), 1);

    cart_destroy(cart);
    free(item);

}

void test_cart_add_existing()
{
    char *name = "car", *desc = "a fast car";
    size_t price = 99; 

    cart_t *cart = cart_create();

    item_t *item = create_item(name, desc, price);
    cart_add(cart, item, 2);
    CU_ASSERT_EQUAL(cart_amount(cart, item), 2);
    cart_add(cart, item, 1);
    CU_ASSERT_EQUAL(cart_amount(cart, item), 3);

    cart_destroy(cart);
    free(item);

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
    free(item);

}

void test_cart_remove_some()
{
    char *name = "car", *desc = "a fast car";
    size_t price = 99, amount = 2; 

    cart_t *cart = cart_create();

    item_t *item = create_item(name, desc, price);
    cart_add(cart, item, amount);
    CU_ASSERT_EQUAL(cart_amount(cart, item), amount);
    cart_remove(cart, item, amount - 1);
    CU_ASSERT_EQUAL(cart_amount(cart, item), 1);

    cart_destroy(cart);
    free(item);

}

void test_cart_remove_none()
{
    char *name = "car", *desc = "a fast car";
    size_t price = 99, amount = 2; 

    cart_t *cart = cart_create();

    item_t *item = create_item(name, desc, price);

    CU_ASSERT_FALSE(cart_remove(cart, item, amount))

    cart_destroy(cart);
    free(item);
}

// ---------------------------------------------------------
// Get items
// ---------------------------------------------------------

void test_cart_get_items()
{
    int item_amount = 6;
    char *names[] = {"monkey", "ape", "orangutan", "chimp", "human", "neanderthal"};
    char *order[] = {"ape", "chimp", "human", "monkey", "neanderthal", "orangutan"};
    char *desc[] = {"desc1", "desc2", "desc3", "desc4", "desc5", "desc6"};
    item_t *items[item_amount];
    size_t price = 99, amount = 2; 

    cart_t *cart = cart_create();

    for(int i = 0; i < item_amount; i++)
    {
        item_t *item = create_item(names[i], desc[i], price);

        cart_add(cart, item, amount);
    }

    ioopm_list_t *item_list = cart_items(cart);
    ioopm_list_iterator_t *it;
    int index = 0;
    
    for(it = ioopm_list_iterator_create(item_list); 
        !ioopm_list_iterator_at_end(it);
        ioopm_list_iterator_advance(it))
        {
            item_t *item = ioopm_list_iterator_current(it).p;
            
            CU_ASSERT_EQUAL(strcmp(item_name(item), order[index]), 0);
            index++;

            free(item);
        }
    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(item_list);
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

    CU_add_test(suite, "add item to cart once", test_cart_add_once);
    CU_add_test(suite, "add the same item twice", test_cart_add_existing);

    CU_add_test(suite, "remove all of one item", test_cart_remove_all);
    CU_add_test(suite, "reomve some of one item", test_cart_remove_some);
    CU_add_test(suite, "reomve from empty cart", test_cart_remove_none);
    
    CU_add_test(suite, "get all items from cart", test_cart_get_items);



    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}