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


void cart_add(cart_t *cart, char *name, size_t amount)
{
    size_t prior_amount = 0;

    cart_item_t *item;
    ioopm_hash_table_lookup(cart->items, PTR_AS_ELEM(name), &PTR_AS_ELEM(item));
    if (!item)
    {
        create_item(name, )
        ioopm_list_insert(ioopm_hash_table_insert(cart->items, PTR_AS_ELEM(name), PTR_AS_ELEM())
    }
}


bool cart_remove(cart_t *cart, char *name, size_t amount)
{
    // lookup stock in cart prior to removal
    value_t cart_item_ptr;
    ioopm_hash_table_lookup(cart->items, PTR_AS_ELEM(name), &cart_item_ptr);

    cart_item_t *cart_item = cart_item_ptr.p;

    if (amount > cart_item->amount)
    {
        return false;
    }
    else if (amount == cart_item->amount)
    {
        return ioopm_hash_table_remove(cart->items, PTR_AS_ELEM(name), &PTR_AS_ELEM(cart_item));
    }
    else
    {
        cart_item->amount--;
        return true;
    }
}


size_t cart_amount(cart_t *cart, char *name)
{
    // get the amount
    value_t amount_ptr = PTR_AS_ELEM(NULL);
    if (!ioopm_hash_table_lookup(cart->items, PTR_AS_ELEM(name), &amount_ptr)) return 0;
    size_t *amount = amount_ptr.p;
    return *amount;
}
