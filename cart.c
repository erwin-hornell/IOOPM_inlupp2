#include <string.h>
#include <stdlib.h>

#include "db.h"
#include "utils.h"

#include "../IOOPM_inlupp1/hash_table.h"
#include "../IOOPM_inlupp1/hash_table_iterator.h"

#include "../IOOPM_inlupp1/linked_list.h"
#include "../IOOPM_inlupp1/linked_list_iterator.h"


struct cart_item
{
    item_t *item;
    size_t amount;
};
typedef struct cart_item cart_item_t;


struct cart
{
    ioopm_hash_table_t *items; // hash table: (string) name -> *cart_item
};
typedef struct cart cart_t;

cart_item_t *cart_item_create(item_t *item, size_t amount)
{
    cart_item_t *cart_item = calloc(1, sizeof(cart_item_t));
    cart_item->item = item;
    cart_item->amount = amount;

    return cart_item;
}

cart_t *cart_create()
{
    cart_t *cart = calloc(1, sizeof(cart_t));
    cart->items = ioopm_hash_table_create(str_hash, str_comp);
    return cart;
}


void cart_destroy(cart_t *cart)
{
    ioopm_hash_table_destroy(cart->items);
    free(cart);
}

void cart_add(cart_t *cart, item_t *item, size_t amount)
{
    // lookup item
    value_t cart_item_v;
    if (ioopm_hash_table_lookup(cart->items, PTR_AS_ELEM(item_name(item)), &cart_item_v))
    { // item type already in cart
        cart_item_t *cart_item = cart_item_v.p;
        cart_item->amount += amount;
    }
    else
    { // item type not already in cart
        cart_item_t *cart_item = cart_item_create(item, amount);
        ioopm_hash_table_insert(cart->items, PTR_AS_ELEM(item_name(item)), PTR_AS_ELEM(cart_item));
    }
}