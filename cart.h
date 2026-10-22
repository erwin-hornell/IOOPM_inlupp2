#pragma once

#include <string.h>

#include "db.h"
#include "cart.c"

#include "../IOOPM_inlupp1/hash_table.h"
#include "../IOOPM_inlupp1/hash_table_iterator.h"

#include "../IOOPM_inlupp1/linked_list.h"
#include "../IOOPM_inlupp1/linked_list_iterator.h"

typedef struct cart cart_t;


/// @brief creates a cart
/// @return pointer to cart
cart_t *cart_create();


/// @brief destroys a cart
/// @param cart a cart
void cart_destroy(cart_t *cart);


/// @brief adds some quantity of a merch to the cart
/// @param cart a cart
/// @param item an item
/// @param amount how many to add to the cart
/// @return boolean representing if merch was sucessfully added to cart
/// @note ensure add is valid before calling, does not take ownership of data
void cart_add(cart_t *cart, item_t *item, size_t amount);


/// @brief removes some quantity of a merch from the cart
/// @param cart a cart
/// @param name the name of some merch in the database
/// @param amount how many to remove from the cart
/// @return boolean representing if merch was sucessfully removed cart
bool cart_remove(cart_t *cart, item_t *item, size_t amount);


/// @brief how many of a given ware is in a cart
/// @param cart a cart
/// @param name a ware name
/// @return number of given ware in the cart
size_t cart_amount(cart_t *cart, item_t *item);

/// @brief gets all items in a cart
/// @param cart a cart
/// @return list of item_t
ioopm_list_t cart_items(cart_t *cart);