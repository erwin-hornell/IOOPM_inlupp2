#pragma once
#include "hash_table.h"
#include <stdbool.h>

/**
* @file hash_table_iterator.h
* @author Erwin Hörnell, Hjalmar Johansson
* @date 17/9/2026
* @brief Iterator for ioopm_hash_table
*
*/

typedef struct hash_table_iterator ioopm_hash_table_iterator_t;




/// @brief Create an iterator for a hash table.
/// @param ht hash table to iterate over
/// @return a new iterator positioned at the first entry if it exists, and positioned at-the-end if ht is empty
ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht);

/// @brief Destroy an iterator and free its memory
/// @param it iterator to destroy
void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it);

/// @brief Check if the current element exists, or equivalently, if it is positioned at an entry
/// @param it iterator operated upon
/// @return true iff the current element exists
bool ioopm_hash_table_iterator_at_end(ioopm_hash_table_iterator_t *it);

/// @brief Move the iterator forward to the next entry if it exists or to at-the-end if no more entries exist
/// @pre it is positioned at an entry
/// @param it iterator operated upon
void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it);

/// @brief Get the key of the current entry
/// @pre it is positioned at an entry
/// @param it iterator operated upon
/// @return the key of the current entry
value_t ioopm_hash_table_iterator_current_key(ioopm_hash_table_iterator_t *it);

/// @brief Get the value of the current entry
/// @pre it is positioned at an entry
/// @param it iterator operated upon
/// @return the value if the current entry
value_t ioopm_hash_table_iterator_current_value(ioopm_hash_table_iterator_t *it);