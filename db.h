#pragma once
#include <stdbool.h>
#include "utils.h"
#include "../IOOPM_inlupp1/hash_table.h"
#include "../IOOPM_inlupp1/hash_table_iterator.h"

#include "../IOOPM_inlupp1/linked_list.h"
#include "../IOOPM_inlupp1/linked_list_iterator.h"

typedef struct db db_t;

/// @brief creates a database
/// @return database pointer
db_t *create_db();

/// @brief destroys merch,
/// @param db database to destroy
void destroy_db(db_t *db);


/// @brief inserts a new item (type) into the db if it isnt already there
/// @param db database that will be added to
/// @param name name of item
/// @param desc descrition of item
/// @param price price in SEK
/// @return true if addition was successful
/// @note takes ownership of strings? (copies?)
bool add_merch(db_t *db, char *name, char *desc, int price);


/// @brief removes an item from the db and all its stock
/// @param db database to remove from
/// @param name name of item to remove
/// @return true if removal was successfull
/// @note does not take ownership of data
bool remove_merch(db_t *db, char *name);


/// @brief edits a database item with new values, it keeps its stock and locations
/// @param db database to edit
/// @param name name of item to edit
/// @param new_name new name of item
/// @param new_desc new desc of item
/// @param new_price new price of item
/// @return true if edit was successfull
/// @note does not take ownership of data
bool edit_merch(db_t *db, char *name, char *new_name, char* new_desc, size_t new_price);


/// @brief returns the item with the given name
/// @param db database to look in
/// @param name a ware's name
/// @param res the item with that name
/// @return boolean representing if ware label was valid (present in database)
/// @note does not take ownership of data
bool get_merch(db_t *db, char *name, item_t **res);


/// @brief adds a given stock to the database
/// @param db database to modify
/// @param name name of the ware
/// @param loca shelf to store the ware
/// @param amount how many of the given stock to add
/// @return boolean representing if ware label was valid (present in database)
/// @note does not take ownership of data
bool add_stock(db_t *db, char *name, char *loca, size_t amount);


/// @brief where (shelfs) a given ware is stored
/// @param db database to look in
/// @param name a ware's name
/// @param locs becomes list of shelfs where the ware is stored
/// @return boolean representing if ware label was valid (present in database)
/// @note does not take ownership of data
bool get_locs(db_t *db, char *name, ioopm_list_t **locs);


/// @brief how many of a given ware is in stock
/// @param db database to look in
/// @param name a ware's name
/// @param res where to write result to (int)
/// @return boolean representing if ware label was valid (present in database)
/// @note does not take ownership of data
bool get_stock(db_t *db, char *name, size_t *res);


/// @brief returns a list of with all the items in the db
/// @param db database to get from
/// @return a list with all the items in alphabetical order
ioopm_list_t *get_all_items(db_t *db);
