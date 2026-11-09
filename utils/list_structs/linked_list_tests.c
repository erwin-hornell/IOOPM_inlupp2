#include <CUnit/Basic.h>
#include <stdbool.h>
#include "linked_list.h"
#include "linked_list_iterator.h"

// ---------------------------------------------------------
// Create / destroy
// ---------------------------------------------------------

void test_list_create(void)
{
    ioopm_list_t *list = ioopm_list_create();

    CU_ASSERT_PTR_NOT_NULL(list);

    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Append
// ---------------------------------------------------------

void test_list_append_once(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(10));

    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 10);

    ioopm_list_destroy(list);
}

void test_list_append(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(10));
    ioopm_list_append(list, INT_AS_ELEM(20));
    ioopm_list_append(list, INT_AS_ELEM(30));

    CU_ASSERT_EQUAL(ioopm_list_size(list), 3);

    CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 10);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 20);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 2).i, 30);

    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Prepend
// ---------------------------------------------------------

void test_list_prepend_once(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_prepend(list, INT_AS_ELEM(10));

    CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 10);

    ioopm_list_destroy(list);
}

void test_list_prepend(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_prepend(list, INT_AS_ELEM(10));
    ioopm_list_prepend(list, INT_AS_ELEM(20));
    ioopm_list_prepend(list, INT_AS_ELEM(30));

    CU_ASSERT_EQUAL(ioopm_list_size(list), 3);

    CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 30);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 20);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 2).i, 10);

    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Head
// ---------------------------------------------------------

void test_list_head(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(42));
    ioopm_list_append(list, INT_AS_ELEM(99));

    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 42);

    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Last
// ---------------------------------------------------------

void test_list_last(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(42));
    ioopm_list_append(list, INT_AS_ELEM(99));

    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 99);

    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Insert
// ---------------------------------------------------------

void test_list_insert_at_front(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(20));
    ioopm_list_append(list, INT_AS_ELEM(30));

    ioopm_list_insert(list, 0, INT_AS_ELEM(10));

    CU_ASSERT_EQUAL(ioopm_list_size(list), 3);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 10);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 20);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 2).i, 30);

    ioopm_list_destroy(list);
}

void test_list_insert_middle(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(10));
    ioopm_list_append(list, INT_AS_ELEM(30));

    ioopm_list_insert(list, 1, INT_AS_ELEM(20));

    CU_ASSERT_EQUAL(ioopm_list_size(list), 3);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 10);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 20);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 2).i, 30);

    ioopm_list_destroy(list);
}

void test_list_insert_at_end(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(10));
    ioopm_list_append(list, INT_AS_ELEM(20));

    ioopm_list_insert(list, 2, INT_AS_ELEM(30));

    CU_ASSERT_EQUAL(ioopm_list_size(list), 3);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 2).i, 30);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 30);

    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Remove
// ---------------------------------------------------------

void test_list_remove_first(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(10));
    ioopm_list_append(list, INT_AS_ELEM(20));
    ioopm_list_append(list, INT_AS_ELEM(30));

    value_t removed = ioopm_list_remove(list, 0);

    CU_ASSERT_EQUAL(removed.i, 10);
    CU_ASSERT_EQUAL(ioopm_list_size(list), 2);
    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 20);

    ioopm_list_destroy(list);
}

void test_list_remove_middle(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(10));
    ioopm_list_append(list, INT_AS_ELEM(20));
    ioopm_list_append(list, INT_AS_ELEM(30));

    value_t removed = ioopm_list_remove(list, 1);

    CU_ASSERT_EQUAL(removed.i, 20);
    CU_ASSERT_EQUAL(ioopm_list_size(list), 2);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 10);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 30);

    ioopm_list_destroy(list);
}

void test_list_remove_last(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(10));
    ioopm_list_append(list, INT_AS_ELEM(20));
    ioopm_list_append(list, INT_AS_ELEM(30));

    value_t removed = ioopm_list_remove(list, 2);

    CU_ASSERT_EQUAL(removed.i, 30);
    CU_ASSERT_EQUAL(ioopm_list_size(list), 2);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 20);

    ioopm_list_destroy(list);
}

void test_list_remove_only_element(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(42));

    value_t removed = ioopm_list_remove(list, 0);

    CU_ASSERT_EQUAL(removed.i, 42);
    CU_ASSERT_EQUAL(ioopm_list_size(list), 0);
    CU_ASSERT_TRUE(ioopm_list_is_empty(list));

    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Get
// ---------------------------------------------------------

void test_list_get(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(10));
    ioopm_list_append(list, INT_AS_ELEM(20));
    ioopm_list_append(list, INT_AS_ELEM(30));

    CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 10);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 20);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 2).i, 30);

    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Size
// ---------------------------------------------------------

void test_list_size(void)
{
    ioopm_list_t *list = ioopm_list_create();

    CU_ASSERT_EQUAL(ioopm_list_size(list), 0);

    ioopm_list_append(list, INT_AS_ELEM(10));
    CU_ASSERT_EQUAL(ioopm_list_size(list), 1);

    ioopm_list_append(list, INT_AS_ELEM(20));
    CU_ASSERT_EQUAL(ioopm_list_size(list), 2);

    ioopm_list_remove(list, 0);
    CU_ASSERT_EQUAL(ioopm_list_size(list), 1);

    ioopm_list_remove(list, 0);
    CU_ASSERT_EQUAL(ioopm_list_size(list), 0);

    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Is empty
// ---------------------------------------------------------

void test_list_is_empty(void)
{
    ioopm_list_t *list = ioopm_list_create();

    CU_ASSERT_TRUE(ioopm_list_is_empty(list));

    ioopm_list_append(list, INT_AS_ELEM(42));

    CU_ASSERT_FALSE(ioopm_list_is_empty(list));

    ioopm_list_remove(list, 0);

    CU_ASSERT_TRUE(ioopm_list_is_empty(list));

    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Different value_t types
// ---------------------------------------------------------

void test_list_bool(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, BOOL_AS_ELEM(true));
    ioopm_list_append(list, BOOL_AS_ELEM(false));

    CU_ASSERT_TRUE(ioopm_list_get(list, 0).b);
    CU_ASSERT_FALSE(ioopm_list_get(list, 1).b);

    ioopm_list_destroy(list);
}

void test_list_float(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, FLOAT_AS_ELEM(3.14f));
    ioopm_list_append(list, FLOAT_AS_ELEM(2.71f));

    CU_ASSERT_DOUBLE_EQUAL(ioopm_list_get(list, 0).f, 3.14f, 0.001);

    CU_ASSERT_DOUBLE_EQUAL(ioopm_list_get(list, 1).f, 2.71f, 0.001);

    ioopm_list_destroy(list);
}

void test_list_pointer(void)
{
    ioopm_list_t *list = ioopm_list_create();

    int x = 10;
    int y = 20;

    ioopm_list_append(list, PTR_AS_ELEM(&x));
    ioopm_list_append(list, PTR_AS_ELEM(&y));

    CU_ASSERT_PTR_EQUAL(ioopm_list_get(list, 0).p, &x);
    CU_ASSERT_PTR_EQUAL(ioopm_list_get(list, 1).p, &y);

    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Iterator Create / destroy
// ---------------------------------------------------------

void test_iterator_create(void)
{
    ioopm_list_t *list = ioopm_list_create();

    CU_ASSERT_PTR_NOT_NULL(list);

    ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);

    CU_ASSERT_PTR_NOT_NULL(it);

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Iterator At End
// ---------------------------------------------------------

void test_iterator_at_end(void)
{
    ioopm_list_t *list = ioopm_list_create();

    CU_ASSERT_PTR_NOT_NULL(list);

    ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);

    CU_ASSERT_TRUE(ioopm_list_iterator_at_end(it));

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Iterator Advance
// ---------------------------------------------------------

void test_iterator_advance(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(10));

    ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);

    CU_ASSERT_FALSE(ioopm_list_iterator_at_end(it));
    ioopm_list_iterator_advance(it);
    CU_ASSERT_TRUE(ioopm_list_iterator_at_end(it));

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Iterator Loop
// ---------------------------------------------------------

void test_iterator_loop(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(10));
    ioopm_list_append(list, INT_AS_ELEM(20));
    ioopm_list_append(list, INT_AS_ELEM(30));

    int values[] = {10, 20, 30};
    int index = 0;
    ioopm_list_iterator_t *it;

    for (it = ioopm_list_iterator_create(list);
         ioopm_list_iterator_at_end(it);
         ioopm_list_iterator_advance(it))
    {
        CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, values[index]);
        index++;
    }

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Iterator Remove
// ---------------------------------------------------------

void test_iterator_remove_first(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(10));
    ioopm_list_append(list, INT_AS_ELEM(20));
    ioopm_list_append(list, INT_AS_ELEM(30));

    ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);

    CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 10);
    CU_ASSERT_EQUAL(ioopm_list_iterator_remove(it).i, 10);

    CU_ASSERT_EQUAL(ioopm_list_size(list), 2);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 20);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 30);

    // Iterator should now point at 20
    CU_ASSERT_FALSE(ioopm_list_iterator_at_end(it));
    CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 20);

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(list);
}

void test_iterator_remove_middle(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(10));
    ioopm_list_append(list, INT_AS_ELEM(20));
    ioopm_list_append(list, INT_AS_ELEM(30));

    ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);

    // Move to 20
    ioopm_list_iterator_advance(it);

    CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 20);
    CU_ASSERT_EQUAL(ioopm_list_iterator_remove(it).i, 20);

    CU_ASSERT_EQUAL(ioopm_list_size(list), 2);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 10);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 30);

    // Iterator should now point at 30
    CU_ASSERT_FALSE(ioopm_list_iterator_at_end(it));
    CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 30);

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(list);
}

void test_iterator_remove_last(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(10));
    ioopm_list_append(list, INT_AS_ELEM(20));
    ioopm_list_append(list, INT_AS_ELEM(30));

    ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);

    // Move to 30
    ioopm_list_iterator_advance(it);
    ioopm_list_iterator_advance(it);

    CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 30);
    CU_ASSERT_EQUAL(ioopm_list_iterator_remove(it).i, 30);

    CU_ASSERT_EQUAL(ioopm_list_size(list), 2);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 10);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 20);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 20);

    // There should be no current element
    CU_ASSERT_TRUE(ioopm_list_iterator_at_end(it));

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(list);
}

void test_iterator_remove_only_element(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(10));

    ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);

    CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 10);
    CU_ASSERT_EQUAL(ioopm_list_iterator_remove(it).i, 10);

    CU_ASSERT_EQUAL(ioopm_list_size(list), 0);

    CU_ASSERT_TRUE(ioopm_list_iterator_at_end(it));

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Iterator Insert
// ---------------------------------------------------------

void test_iterator_insert_first(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(20));
    ioopm_list_append(list, INT_AS_ELEM(30));

    ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);

    // Current = 20
    // Insert 10 before current
    ioopm_list_iterator_insert(it, INT_AS_ELEM(10));

    CU_ASSERT_EQUAL(ioopm_list_size(list), 3);

    CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 10);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 20);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 2).i, 30);

    // Iterator should still point at 20
    CU_ASSERT_FALSE(ioopm_list_iterator_at_end(it));
    CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 20);

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(list);
}

void test_iterator_insert_middle(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(10));
    ioopm_list_append(list, INT_AS_ELEM(30));

    ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);

    // Current = 30
    ioopm_list_iterator_advance(it);

    // Insert 20 before current
    ioopm_list_iterator_insert(it, INT_AS_ELEM(20));

    CU_ASSERT_EQUAL(ioopm_list_size(list), 3);

    CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 10);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 20);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 2).i, 30);

    // Iterator should still point at 30
    CU_ASSERT_FALSE(ioopm_list_iterator_at_end(it));
    CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 30);

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(list);
}

void test_iterator_insert_last(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_append(list, INT_AS_ELEM(10));
    ioopm_list_append(list, INT_AS_ELEM(20));

    ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);

    // Current = 20
    ioopm_list_iterator_advance(it);

    // Insert 30 before current.
    // Since 20 is last, this checks insertion at the end.
    ioopm_list_iterator_insert(it, INT_AS_ELEM(30));

    CU_ASSERT_EQUAL(ioopm_list_size(list), 3);

    CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 10);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 30);
    CU_ASSERT_EQUAL(ioopm_list_get(list, 2).i, 20);

    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 20);

    // Iterator should still point at 20
    CU_ASSERT_FALSE(ioopm_list_iterator_at_end(it));
    CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 20);

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(list);
}

void test_iterator_insert_empty(void)
{
    ioopm_list_t *list = ioopm_list_create();

    ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);

    ioopm_list_iterator_insert(it, INT_AS_ELEM(10));

    CU_ASSERT_EQUAL(ioopm_list_size(list), 1);

    CU_ASSERT_EQUAL(ioopm_list_get(list, 0).i, 10);
    CU_ASSERT_EQUAL(ioopm_list_head(list).i, 10);
    CU_ASSERT_EQUAL(ioopm_list_last(list).i, 10);
    
    CU_ASSERT_FALSE(ioopm_list_iterator_at_end(it));
    CU_ASSERT_EQUAL(ioopm_list_iterator_current(it).i, 10);
 

    ioopm_list_iterator_destroy(it);
    ioopm_list_destroy(list);
}

// ---------------------------------------------------------
// Main
// ---------------------------------------------------------

int main(void)
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite(
        "Linked List Tests",
        NULL,
        NULL);

    CU_add_test(suite, "Create", test_list_create);

    CU_add_test(suite, "Append once", test_list_append_once);
    CU_add_test(suite, "Append", test_list_append);

    CU_add_test(suite, "Prepend once", test_list_prepend_once);
    CU_add_test(suite, "Prepend", test_list_prepend);

    CU_add_test(suite, "Head", test_list_head);
    CU_add_test(suite, "Last", test_list_last);

    CU_add_test(suite, "Insert at front", test_list_insert_at_front);
    CU_add_test(suite, "Insert middle", test_list_insert_middle);
    CU_add_test(suite, "Insert at end", test_list_insert_at_end);

    CU_add_test(suite, "Remove first", test_list_remove_first);
    CU_add_test(suite, "Remove middle", test_list_remove_middle);
    CU_add_test(suite, "Remove last", test_list_remove_last);
    CU_add_test(suite, "Remove only element", test_list_remove_only_element);

    CU_add_test(suite, "Get", test_list_get);
    CU_add_test(suite, "Size", test_list_size);
    CU_add_test(suite, "Is empty", test_list_is_empty);

    CU_add_test(suite, "Bool values", test_list_bool);
    CU_add_test(suite, "Float values", test_list_float);
    CU_add_test(suite, "Pointer values", test_list_pointer);

    CU_add_test(suite, "Create & Destroy iterator", test_iterator_create);
    CU_add_test(suite, "Is at end of empty iterator", test_iterator_at_end);
    CU_add_test(suite, "Advance iterator once", test_iterator_advance);
    CU_add_test(suite, "Simple iterator for loop", test_iterator_loop);

    CU_add_test(suite, "Remove first", test_iterator_remove_first);
    CU_add_test(suite, "Remove middle", test_iterator_remove_middle);
    CU_add_test(suite, "Remove last", test_iterator_remove_last);
    CU_add_test(suite, "Remove only element", test_iterator_remove_only_element);

    CU_add_test(suite, "Insert first", test_iterator_insert_first);
    CU_add_test(suite, "Insert midle", test_iterator_insert_middle);
    CU_add_test(suite, "Insert last", test_iterator_insert_last);
    CU_add_test(suite, "Insert into empty list", test_iterator_insert_empty);


    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}
