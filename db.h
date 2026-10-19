#pragma once
#include <stdbool.h>
#include "../IOOPM_inlupp1/hash_table.h"
#include "../IOOPM_inlupp1/hash_table_iterator.h"

#include "../IOOPM_inlupp1/linked_list.h"
#include "../IOOPM_inlupp1/linked_list_iterator.h"

typedef struct db db_t;


db_t *create_db();

/// @brief destroys merch,
/// @param db database to destroy
void destroy_db(db_t *db);


/// @brief inserts a new item into the db if it isnt already there
/// @param db database that will be added to
/// @param name name of item
/// @param desc descrition of item
/// @param price price in SEK
/// @return true if addition was successfull
/// @note takes ownership of strings
bool add_merch(db_t *db, char *name, char *desc, int price);


/// @brief removes an item from the db and all its stock
/// @param db database to remove from
/// @param name name of item to remove
/// @return true if removal was successfull
/// @note dosnt take ownership of string
bool remove_merch(db_t *db, char *name);

bool edit_merch(db_t *db, char *name, char *new_name, char* new_desc, size_t new_price);

/// @note dosnt take ownership of string
bool add_stock(db_t *db, char *name, char *loca, size_t amount);

/// @note dosnt take ownership of string
bool get_locs(db_t *db, char *name, ioopm_list_t **locs);

/// @note dosnt take ownership of string
bool get_stock(db_t *db, char *name, size_t *res);

ioopm_list_t *get_all_items(db_t *db);
