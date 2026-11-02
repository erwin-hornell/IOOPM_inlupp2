#pragma once

#include "generics/generics.h"

#include "../IOOPM_inlupp1/hash_table.h"
#include "../IOOPM_inlupp1/hash_table_iterator.h"

#include "../IOOPM_inlupp1/linked_list.h"
#include "../IOOPM_inlupp1/linked_list_iterator.h"


typedef struct shop shop_t;

/// @brief creates a shop with an empty db and no carts
/// @return an empty shop
shop_t *shop_create();

/// @brief destroys a shop
/// @param shop 
void shop_destroy(shop_t *shop);

/// @brief adds a new item to the shops database
/// @param shop to add to
/// @param name of item
/// @param desc of item
/// @param price of item
/// @return true if item was added
/// @note name must be uniqe
bool add_to_db(shop_t *shop, char *name, char *desc, size_t price);

/// @brief removes an item type from db
/// @param shop 
/// @param name of item to remove
/// @return true if item was removed successfully
bool remove_from_db(shop_t *shop, char *name);


/// @brief edits an item in the database
/// @param shop to edit in
/// @param name of the item to edit
/// @param new_name 
/// @param new_desc 
/// @param new_price 
/// @return true if edit went through
/// @note the new name must be uniqe
bool edit_item(shop_t *shop, char *name, char *new_name, char *new_desc, size_t new_price);

/// @brief returns all items in the database
/// @param shop
/// @return a list of all items in the database
ioopm_list_t *list_db(shop_t *shop);

/// @brief returns all locations whare an item is stored
/// @param shop a shop
/// @param name item name
/// @return a linked list of strings representing locations where the given item is stored
/// @note ownership of list is inherited upon creation
ioopm_list_t *get_merch_locs(shop_t *shop, char *name);

/// @brief adds increases the amount stored at a location or adds a new location to an item
/// @param shop 
/// @param name of item
/// @param loc name of the location
/// @param amount to be added
/// @return true if operation was successful
bool db_replenish(shop_t *shop, char *name, char *loc, size_t amount);

/// @brief adds a new empty cart to the shop
/// @param shop 
void new_cart(shop_t *shop);

/// @brief removes a cart from the shop
/// @param shop 
/// @param id 
/// @return true if cart was removed
bool remove_cart(shop_t *shop, size_t id);

/// @brief returns a list of all items in a cart
/// @param shop 
/// @param id of cart
/// @param items becomes a list of all items in the cart
/// @return true if cart could be found
bool cart_get_all_items(shop_t *shop, size_t id, ioopm_list_t **items);

/// @brief adds a new item to a cart
/// @param shop 
/// @param id of cart
/// @param item to be added
/// @param amount to add
/// @return true if addition was successful
bool add_to_cart(shop_t *shop, size_t id, char *name, size_t amount);

/// @brief removes an amount of an item from a cart
/// @param shop 
/// @param id of the cart
/// @param item to be removed
/// @param amount to remove
/// @return true if items where successfully removed
bool remove_from_cart(shop_t *shop, size_t id, item_t *item, size_t amount);

/// @brief checksout cart
/// @param shop to check out from
/// @param id of cart to checkout
/// @return returns true if all items could be checked out
/// @note will only checkout of all items can be checkedout
bool checkout_cart(shop_t *shop, size_t id);