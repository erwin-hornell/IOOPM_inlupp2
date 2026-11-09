#include <CUnit/Basic.h>
#include "hash_table.h"
#include "hash_table_iterator.h"

int init_suite(void)
{
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void)
{
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

// These are example test functions. You should replace them with
// functions of your own.
void test_create_destroy()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);
  CU_ASSERT_PTR_NOT_NULL(ht);
  ioopm_hash_table_destroy(ht);
}

void test_look_up_empty()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  char *key = "abc";

  // check that key is not in ht
  int result = 0;
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, PTR_AS_ELEM(key), &INT_AS_ELEM(result)));
  CU_ASSERT_EQUAL(result, 0);

  ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  char *key = "abc";
  int value = 123;

  // check that key is not in ht
  value_t result;
  result.i = 0;
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, PTR_AS_ELEM(key), &result));
  CU_ASSERT_EQUAL(result.i, 0);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key), INT_AS_ELEM(value));
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, PTR_AS_ELEM(key), &result));
  CU_ASSERT_EQUAL(result.i, value);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_insert_update()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  char *key = "abc";
  value_t result;
  int value1 = 123;
  int value2 = 456;
  result.i = 0;

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key), INT_AS_ELEM(value1));
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, PTR_AS_ELEM(key), &result));
  CU_ASSERT_EQUAL(result.i, value1);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key), INT_AS_ELEM(value2));
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, PTR_AS_ELEM(key), &result));
  CU_ASSERT_EQUAL(result.i, value2);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_remove_empty()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  char *key = "abc";
  int res = 0;
  // insert key-value pair and check that the mapping exists
  CU_ASSERT_FALSE(ioopm_hash_table_remove(ht, PTR_AS_ELEM(key), &INT_AS_ELEM(res)));

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_remove_existing()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  char *key = "abc";
  int value = 123;

  // check that key is not in ht
  value_t res_lookup, res_remove;
  res_lookup.i = 0;
  res_remove.i = 0;

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key), INT_AS_ELEM(value));
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, PTR_AS_ELEM(key), &res_lookup));
  CU_ASSERT_EQUAL(res_lookup.i, value);

  CU_ASSERT_TRUE(ioopm_hash_table_remove(ht, PTR_AS_ELEM(key), &res_remove));
  CU_ASSERT_EQUAL(res_remove.i, value);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, PTR_AS_ELEM(key), &res_lookup));

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_has_key_empty()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  char *key = "abc";
  // insert key-value pair and check that the mapping exists
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, PTR_AS_ELEM(key)));

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}
void test_has_key_twice()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  char *key1 = "abc";
  int val1 = 123;
  char *key2 = "def";

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key1), INT_AS_ELEM(val1));

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, PTR_AS_ELEM(key1)));

  // Check non existing key
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, PTR_AS_ELEM(key2)));

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_has_key_thrice()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  char *key1 = "a";
  char *key2 = "b";
  char *key3 = "c";
  char *key4 = "d";
  int val1 = 123;
  int val2 = 456;
  int val3 = 789;

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key1), INT_AS_ELEM(val1));
  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key2), INT_AS_ELEM(val2));
  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key3), INT_AS_ELEM(val3));

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, PTR_AS_ELEM(key1)));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, PTR_AS_ELEM(key2)));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, PTR_AS_ELEM(key3)));

  // Check non existing key
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, PTR_AS_ELEM(key4)));

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_has_key_removed()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  char *key1 = "abc";
  int val1 = 123;
  int res = 0;

  // insert key-value pair, remove it and check that the mapping exists
  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key1), INT_AS_ELEM(val1));
  ioopm_hash_table_remove(ht, PTR_AS_ELEM(key1), &INT_AS_ELEM(res));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, PTR_AS_ELEM(key1)));

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_has_key_removed_twice()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  char *key1 = "a";
  char *key2 = "b";
  char *key3 = "c";
  int val1 = 123;
  int val2 = 456;
  int val3 = 789;

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key1), INT_AS_ELEM(val1));
  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key2), INT_AS_ELEM(val2));
  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key3), INT_AS_ELEM(val3));

  int res = 0;
  ioopm_hash_table_remove(ht, PTR_AS_ELEM(key2), &INT_AS_ELEM(res));

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, PTR_AS_ELEM(key1)));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, PTR_AS_ELEM(key3)));

  // Check non existing key
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, PTR_AS_ELEM(key2)));

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_size_empty()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  // Size of empty ht
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_size_one_entry()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);
  char *key = "a";
  int val = 123;

  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key), INT_AS_ELEM(val));
  // Size of ht
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 1);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_size_mult()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);
  int size = 7;
  char *keys[] = {"a", "b", "c", "d", "e", "f", "g"};
  int vals[] = {1, 2, 3, 4, 5, 6, 7};

  for (int i = 0; i < size; i++)
  {
    ioopm_hash_table_insert(ht, PTR_AS_ELEM(keys[i]), INT_AS_ELEM(vals[i]));
  }

  // Size of ht
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), size);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_size_remove()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);
  char *key = "a";
  int val = 123;
  int res = 0;

  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key), INT_AS_ELEM(val));

  ioopm_hash_table_remove(ht, PTR_AS_ELEM(key), &INT_AS_ELEM(res));

  // Size of ht
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_size_remove_mult()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  int size = 7;
  char *keys[] = {"a", "b", "c", "d", "e", "f", "g"};
  int vals[] = {1, 2, 3, 4, 5, 6, 7};
  int res = 0;
  for (int i = 0; i < size; i++)
  {
    ioopm_hash_table_insert(ht, PTR_AS_ELEM(keys[i]), INT_AS_ELEM(vals[i]));
  }

  ioopm_hash_table_remove(ht, PTR_AS_ELEM(keys[2]), &INT_AS_ELEM(res));
  // Size of ht
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), size - 1);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_is_empty_empty()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  // Size of empty ht
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_is_empty_one_entry()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);
  char *key = "a";
  int val = 123;

  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key), INT_AS_ELEM(val));
  // Size of ht
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_is_empty_mult()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);
  int size = 7;
  char *keys[] = {"a", "b", "c", "d", "e", "f", "g"};
  int vals[] = {1, 2, 3, 4, 5, 6, 7};

  for (int i = 0; i < size; i++)
  {
    ioopm_hash_table_insert(ht, PTR_AS_ELEM(keys[i]), INT_AS_ELEM(vals[i]));
  }

  // Size of ht
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_is_empty_remove()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);
  char *key = "a";
  int val = 123;
  int res = 0;

  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key), INT_AS_ELEM(val));

  ioopm_hash_table_remove(ht, PTR_AS_ELEM(key), &INT_AS_ELEM(res));

  // Size of ht
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_is_empty_remove_mult()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  int size = 7;
  char *keys[] = {"a", "b", "c", "d", "e", "f", "g"};
  int vals[] = {1, 2, 3, 4, 5, 6, 7};
  int res = 0;
  for (int i = 0; i < size; i++)
  {
    ioopm_hash_table_insert(ht, PTR_AS_ELEM(keys[i]), INT_AS_ELEM(vals[i]));
  }

  ioopm_hash_table_remove(ht, PTR_AS_ELEM(keys[2]), &INT_AS_ELEM(res));
  // Size of ht
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_iterator_once()
{
  char *key = "a";
  int val = 123;
  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  ioopm_hash_table_insert(ht, PTR_AS_ELEM(key), INT_AS_ELEM(val));

  int iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);

  CU_ASSERT_EQUAL(iteration_count, 1);
}

void test_iterator_empty()
{

  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  int iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
  CU_ASSERT_EQUAL(iteration_count, 0);
}

void test_iterator_several_entries()
{
  char *keys[3] = {"abc", "qwe", "asd"};
  int values[3] = {0, 1, 2};

  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, PTR_AS_ELEM(keys[i]), INT_AS_ELEM(values[i]));
  }

  int iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
  CU_ASSERT_EQUAL(iteration_count, 3);
}

void test_iterator_visit_exactly_once()
{
  char *keys[3] = {"abc", "qwe", "asd"};
  int values[3] = {0, 0, 0};

  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, PTR_AS_ELEM(keys[i]), INT_AS_ELEM(values[i]));
  }

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    int look_up = 0;
    char *key = (char *)ioopm_hash_table_iterator_current_key(it).p;
    ioopm_hash_table_lookup(ht, PTR_AS_ELEM(key), &INT_AS_ELEM(look_up));
    look_up++;
    ioopm_hash_table_insert(ht, PTR_AS_ELEM(key), INT_AS_ELEM(look_up));
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);

  it = ioopm_hash_table_iterator_create(ht);

  while (!ioopm_hash_table_iterator_at_end(it))
  {

    CU_ASSERT_EQUAL(ioopm_hash_table_iterator_current_value(it).i, 1);
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
}

void test_iterator_several_per_bucket()
{
  char *keys[] = {
      "a", "b", "c", "d", "e", "f",
      "g", "h", "i", "j", "k", "l",
      "m", "n", "o", "p", "q", "r"};

  int values[] = {
      0, 1, 2, 3, 4, 5,
      6, 7, 8, 9, 10, 11,
      12, 13, 14, 15, 16, 17};

  ioopm_hash_table_t *ht = ioopm_hash_table_create(str_hash, str_comp);

  for (int i = 0; i < 18; ++i)
  {
    ioopm_hash_table_insert(ht, PTR_AS_ELEM(keys[i]), INT_AS_ELEM(values[i]));
  }

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);

  int iteration_count = 0;

  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  CU_ASSERT_EQUAL(iteration_count, 18);

  ioopm_hash_table_iterator_destroy(it);
  ioopm_hash_table_destroy(ht);
}

size_t int_hash(const value_t key)
{
  return key.i;
}

bool int_comp(const value_t a, const value_t b)
{
  return a.i == b.i;
}

void test_int_key()
{

  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_hash, int_comp);

  int size = 7;
  int keys[] = {1, 2, 3, 4, 5, 6, 7};
  char *vals[] = {"a", "b", "c", "d", "e", "f", "g"};

  value_t res1, res2;
  res1.p = "res1";
  res2.p = "res2";
  for (int i = 0; i < size; i++)
  {
    ioopm_hash_table_insert(ht, INT_AS_ELEM(keys[i]), PTR_AS_ELEM(vals[i]));
  }

  int to_remove = keys[2];
  CU_ASSERT_TRUE(ioopm_hash_table_remove(ht, INT_AS_ELEM(to_remove), &res1));
  //res should be c
  CU_ASSERT_EQUAL(strcmp(res1.p, vals[2]), 0);
  // Size of ht

  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, INT_AS_ELEM(to_remove), &res2));
  //res2 should not have changed
  CU_ASSERT_EQUAL(strcmp(res2.p, "res2"), 0);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

int main()
{
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite hash_suite = CU_add_suite("Suite to test hash tables", init_suite, clean_suite);
  if (hash_suite == NULL)
  {
    // If the test suite could not be added, tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
      (CU_add_test(hash_suite, "Create & destroy", test_create_destroy) == NULL) ||
      (CU_add_test(hash_suite, "Look up key in empty ht", test_look_up_empty) == NULL) ||
      (CU_add_test(hash_suite, "Insert in ht", test_insert_once) == NULL) ||
      (CU_add_test(hash_suite, "Update existing key", test_insert_update) == NULL) ||
      (CU_add_test(hash_suite, "Remove key from empty ht", test_remove_empty) == NULL) ||
      (CU_add_test(hash_suite, "Remove existing key from ht", test_remove_existing) == NULL) ||

      (CU_add_test(hash_suite, "Has key in empty ht", test_has_key_empty) == NULL) ||
      (CU_add_test(hash_suite, "Has key on existing and non existing keys", test_has_key_twice) == NULL) ||
      (CU_add_test(hash_suite, "Has key on multiple existing and none existing", test_has_key_thrice) == NULL) ||
      (CU_add_test(hash_suite, "Has key on removed key", test_has_key_removed) == NULL) ||
      (CU_add_test(hash_suite, "Has key on multiple keys and removed key", test_has_key_removed_twice) == NULL) ||

      (CU_add_test(hash_suite, "Is empty on empty ht", test_is_empty_empty) == NULL) ||
      (CU_add_test(hash_suite, "Is empty one entry", test_is_empty_one_entry) == NULL) ||
      (CU_add_test(hash_suite, "Is empty on multiple existing and none existing", test_is_empty_mult) == NULL) ||
      (CU_add_test(hash_suite, "Is empty on removed key", test_is_empty_remove) == NULL) ||

      (CU_add_test(hash_suite, "Size on empty ht", test_size_empty) == NULL) ||
      (CU_add_test(hash_suite, "Size one entry", test_size_one_entry) == NULL) ||
      (CU_add_test(hash_suite, "Size on removed key", test_size_remove) == NULL) ||
      (CU_add_test(hash_suite, "Size on larger ht", test_size_remove_mult) == NULL) ||

      (CU_add_test(hash_suite, "Iterates over an empty ht", test_iterator_empty) == NULL) ||
      (CU_add_test(hash_suite, "Iterates over an ht with 1 entry", test_iterator_once) == NULL) ||
      (CU_add_test(hash_suite, "Iterates over multiple entries", test_iterator_several_entries) == NULL) ||
      (CU_add_test(hash_suite, "Iterates each entry exactly once", test_iterator_visit_exactly_once) == NULL) ||
      (CU_add_test(hash_suite, "Iterates over ht with atleast 1 bucket with 2 entries", test_iterator_several_per_bucket) == NULL) ||

      (CU_add_test(hash_suite, "Int as key and string as value", test_int_key) == NULL) ||
      
      0)
  {
    // If adding any of the tests fails, we tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}