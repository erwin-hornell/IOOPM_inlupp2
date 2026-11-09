#pragma once

#include <string.h>

#include "db.h"
#include "../generics/generics.h"


typedef struct cart cart_t;
//leak cart_item to shop so that checkout logics can work
typedef struct cart_item cart_item_t;

/// @brief returns the amount of a item in the cart
/// @param cart_item
/// @return amount of that item in the cart
size_t cart_item_amount(cart_item_t *cart_item);

/// @brief returns the item of the cart_item
/// @param cart_item
/// @return item type of the cart_item
item_t *cart_item_item(cart_item_t *cart_item);

/// @brief creates a cart
/// @param id of the cart
/// @return pointer to cart
cart_t *cart_create(size_t t);


/// @brief destroys a cart
/// @param cart a cart
void cart_destroy(cart_t *cart);


/// @brief returns the id of a cart
/// @param cart
/// @return cart id
size_t cart_id(cart_t *cart);

/// @brief adds some quantity of a merch to the cart
/// @param cart a cart
/// @param item an item
/// @param amount how many to add to the cart
/// @return boolean representing if merch was sucessfully added to cart
/// @note ensure add is valid before calling, does not take ownership of data
void cart_add(cart_t *cart, item_t *item, size_t amount);

/// @brief Removes an item from a cart completly
/// @param cart to remove from
/// @param name of item to delete
/// @return true if removal was successfull
bool cart_delete(cart_t *cart, char *name);


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


/// @brief total cost of all items in cart
/// @param cart a cart
/// @return total cost of all items in cart
size_t cart_cost(cart_t *cart);

/// @brief gets all items in a cart
/// @param cart a cart
/// @return list of item_t
ioopm_list_t *cart_items(cart_t *cart);

/// @brief looks up a cart item in a cart
/// @param cart a cart
/// @param item_name an item's name
/// @return pointer to cart_item_t (NULL if none could be found!)
cart_item_t *cart_lookup(cart_t *cart, char *item_name);