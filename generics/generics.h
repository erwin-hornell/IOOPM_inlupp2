#pragma once
// hash table
#include "../../IOOPM_inlupp1/hash_table.h"
#include "../../IOOPM_inlupp1/hash_table_iterator.h"
// linked list
#include "../../IOOPM_inlupp1/linked_list.h"
#include "../../IOOPM_inlupp1/linked_list_iterator.h"

typedef struct item item_t;

/// @brief creates an item
/// @param name the item's name
/// @param desc the item's description
/// @param price the item's price in SEK
/// @return item pointer
item_t *item_create(char *name, char *desc, int price);

/// @brief destroys an item, freeing its memory
/// @param item an item
void item_destroy(item_t *item);

/// @brief gets the name of an item struct
/// @param item the item
/// @return the item's name
char *item_name(item_t *item);

/// @brief gets the description of an item struct
/// @param item the item
/// @return the item's description
char *item_desc(item_t *item);

/// @brief gets the price of an item struct
/// @param item the item
/// @return the item's price in SEK
int item_price(item_t *item);

//TODO: add description
void item_update_name(item_t *item, char* new_name);
void item_update_desc(item_t *item, char* new_desc);
void item_update_price(item_t *item, int new_price);

void insert_in_order(item_t *to_insert, ioopm_list_t *list);



//TODO: add description
typedef struct shelf shelf_t;

shelf_t *shelf_create(char *name, size_t amount);

void shelf_destroy(shelf_t *shelf);

char *shelf_name(shelf_t *shelf);
size_t shelf_amount(shelf_t *shelf);
void shelf_amount_set(shelf_t *shelf, size_t amount);
void shelf_amount_add(shelf_t *shelf, size_t addend);
void shelf_amount_remove(shelf_t *shelf, size_t addend);




//TODO: add description
size_t int_hash(const value_t key);

bool int_comp(const value_t a, const value_t b);