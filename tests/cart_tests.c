#include <CUnit/Basic.h>
#include <string.h>
#include <stdio.h>
#include "../backend/cart.h"
#include "../generics/generics.h"


// ---------------------------------------------------------
// Create / destroy
// ---------------------------------------------------------

void test_cart_destroy()
{
    cart_t *cart = cart_create(1);
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

    cart_t *cart = cart_create(1);

    item_t *item = item_create(strdup(name), strdup(desc), price);
    cart_add(cart, item, amount);
    CU_ASSERT_EQUAL(cart_amount(cart, item), 1);

    cart_destroy(cart);
    item_destroy(item);

}

void test_cart_add_existing()
{
    char *name = "car", *desc = "a fast car";
    size_t price = 99; 

    cart_t *cart = cart_create(1);

    item_t *item = item_create(strdup(name), strdup(desc), price);;
    cart_add(cart, item, 2);
    CU_ASSERT_EQUAL(cart_amount(cart, item), 2);
    cart_add(cart, item, 1);
    CU_ASSERT_EQUAL(cart_amount(cart, item), 3);

    cart_destroy(cart);
    item_destroy(item);

}

// ---------------------------------------------------------
// Get id
// ---------------------------------------------------------

void test_cart_accessors()
{
    cart_t *cart = cart_create(42);

    char *name = strdup("car");
    char *desc = strdup("fast car");

    item_t *item = item_create(name, desc, 100);
    cart_add(cart, item, 10);
    cart_item_t *cart_item = cart_lookup(cart, name);

    CU_ASSERT_EQUAL(cart_id(cart), 42);
    CU_ASSERT_PTR_EQUAL(cart_item_item(cart_item), item);
    CU_ASSERT_EQUAL(cart_item_amount(cart_item), 5);


    cart_destroy(cart);
    item_destroy(item);
}

// ---------------------------------------------------------
// Lookup cart
// ---------------------------------------------------------

void test_cart_lookup()
{
    cart_t *cart = cart_create(1);

    item_t *item = item_create(
        strdup("car"),
        strdup("fast car"),
        100
    );

    cart_add(cart, item, 5);

    // Existing item
    cart_item_t *result = cart_lookup(cart, "car");

    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_PTR_EQUAL(cart_item_item(result), item);
    CU_ASSERT_EQUAL(cart_item_amount(result), 5);

    // Nonexistent item
    CU_ASSERT_PTR_NULL(cart_lookup(cart, "bike"));

    cart_destroy(cart);
    item_destroy(item);
}


// ---------------------------------------------------------
// Get delete
// ---------------------------------------------------------

void test_cart_delete()
{
    cart_t *cart = cart_create(1);

    item_t *item = item_create(
        strdup("car"),
        strdup("fast car"),
        100
    );

    cart_add(cart, item, 5);

    // Delete an existing item
    CU_ASSERT_TRUE(cart_delete(cart, "car"));

    // Verify that it is gone
    CU_ASSERT_PTR_NULL(cart_lookup(cart, "car"));

    // Try deleting an item that doesn't exist
    CU_ASSERT_FALSE(cart_delete(cart, "car"));

    cart_destroy(cart);
    item_destroy(item);
}

// ---------------------------------------------------------
// Remove
// ---------------------------------------------------------

void test_cart_remove_all()
{
    char *name = "car", *desc = "a fast car";
    size_t price = 99, amount = 1;

    cart_t *cart = cart_create(1);

    item_t *item = item_create(strdup(name), strdup(desc), price);;
    cart_add(cart, item, amount);
    CU_ASSERT_EQUAL(cart_amount(cart, item), amount);
    cart_remove(cart, item, amount);
    CU_ASSERT_EQUAL(cart_amount(cart, item), 0);

    cart_destroy(cart);
    item_destroy(item);

}

void test_cart_remove_some()
{
    char *name = "car", *desc = "a fast car";
    size_t price = 99, amount = 2; 

    cart_t *cart = cart_create(1);

    item_t *item = item_create(strdup(name), strdup(desc), price);;
    cart_add(cart, item, amount);
    CU_ASSERT_EQUAL(cart_amount(cart, item), amount);
    cart_remove(cart, item, amount - 1);
    CU_ASSERT_EQUAL(cart_amount(cart, item), 1);

    cart_destroy(cart);
    item_destroy(item);

}

void test_cart_remove_none()
{
    char *name = "car", *desc = "a fast car";
    size_t price = 99, amount = 2; 

    cart_t *cart = cart_create(1);

    item_t *item = item_create(strdup(name), strdup(desc), price);;

    CU_ASSERT_FALSE(cart_remove(cart, item, amount))

    cart_destroy(cart);
    item_destroy(item);
}

void test_cart_remove_too_much()
{
    cart_t *cart = cart_create(1);

    item_t *item = item_create(
        strdup("car"),
        strdup("fast car"),
        100
    );

    cart_add(cart, item, 5);

    // Try removing more than available
    CU_ASSERT_FALSE(cart_remove(cart, item, 6));

    // Verify that the amount hasn't changed
    CU_ASSERT_EQUAL(cart_amount(cart, item), 5);

    cart_destroy(cart);
    item_destroy(item);
}

// ---------------------------------------------------------
// Get items
// ---------------------------------------------------------

void test_cart_items_empty()
{
    cart_t *cart = cart_create(1);

    ioopm_list_t *items = cart_items(cart);

    CU_ASSERT_PTR_NOT_NULL(items);
    CU_ASSERT_TRUE(ioopm_list_is_empty(items));

    ioopm_list_destroy(items);
    cart_destroy(cart);
}


void test_cart_get_items()
{
    int item_amount = 6;
    char *names[] = {"monkey", "ape", "orangutan", "chimp", "human", "neanderthal"};
    char *order[] = {"ape", "chimp", "human", "monkey", "neanderthal", "orangutan"};
    char *desc[] = {"desc1", "desc2", "desc3", "desc4", "desc5", "desc6"};
    size_t price = 99, amount = 2; 

    cart_t *cart = cart_create(1);

    for(int i = 0; i < item_amount; i++)
    {
        item_t *item = item_create(strdup(names[i]), strdup(desc[i]), price);

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

            item_destroy(item);
        }
    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(item_list);
    cart_destroy(cart);

}

// ---------------------------------------------------------
// Cost
// ---------------------------------------------------------

void test_cart_cost()
{
    cart_t *cart = cart_create(1);

    item_t *car = item_create(
        strdup("car"),
        strdup("fast car"),
        100
    );

    item_t *bike = item_create(
        strdup("bike"),
        strdup("mountain bike"),
        50
    );

    // Empty cart
    CU_ASSERT_EQUAL(cart_cost(cart), 0);

    cart_add(cart, car, 2);
    cart_add(cart, bike, 3);

    // 2 * 100 + 3 * 50 = 350
    CU_ASSERT_EQUAL(cart_cost(cart), 350);

    cart_destroy(cart);
    item_destroy(car);
    item_destroy(bike);
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

    CU_add_test(suite, "add item to cart once", test_cart_add_once);
    CU_add_test(suite, "add the same item twice", test_cart_add_existing);

    CU_add_test(suite, "get id of cart", test_cart_accessors);

    CU_add_test(suite, "Lookup cart", test_cart_lookup);

    CU_add_test(suite, "Delete cart", test_cart_delete);



    CU_add_test(suite, "remove all of one item", test_cart_remove_all);
    CU_add_test(suite, "reomve some of one item", test_cart_remove_some);
    CU_add_test(suite, "reomve from empty cart", test_cart_remove_none);
    CU_add_test(suite, "reomve too much", test_cart_remove_too_much);
    
    CU_add_test(suite, "get all from empty cart", test_cart_items_empty);
    CU_add_test(suite, "get all items from cart", test_cart_get_items);
    
    CU_add_test(suite, "Cart cost",  test_cart_cost);
    

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}