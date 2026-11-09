#pragma once
#include <stdbool.h>
#include "common.h"
#include <string.h>
/**
* @file hash_table.h
* @author Erwin Hörnell, Hjalmar Johansson
* @date 17/9/2026
* @brief Simple hash table that maps string keys to integer values.
*
*/
#define No_buckets 17

typedef struct hash_table ioopm_hash_table_t;



typedef bool ioopm_eq_function(const value_t a, const value_t b);
typedef size_t ioopm_hash_function(const value_t key);

/// @brief hashes keys as strings
/// @return hashed unsinged interger
size_t str_hash(const value_t key);


/// @brief compares keys as strings
/// @return true if the keys match as strings
bool str_comp(const value_t a, const value_t b);

//NOTE: Might have be better add create function for each of the diffrent types of key instead of 
// adding public hash and compare functions

/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *eq_fn);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, const value_t key, value_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @param result ptr to value of the key to lookup, unchaged if failed
/// @return True if the key was found
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, const value_t key, value_t *result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @param result ptr to value of the removed key, unchaged if failed
/// @return True if the key was removed
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, const value_t key, value_t *result);

/// @brief Returns if a given key is in the hash table
/// @param ht hash table we check
/// @param key key to look up
/// @return true if key is present else false
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, const value_t key);

/// @brief Checks if hash table is empty
/// @param ht hash table we check
/// @return true if hash table is empty
bool ioopm_hash_table_is_empty(const ioopm_hash_table_t *ht);

/// @brief Returns size of given hash table
/// @param ht hash table we check
/// @return Size of the hash table
size_t ioopm_hash_table_size(const ioopm_hash_table_t *ht);