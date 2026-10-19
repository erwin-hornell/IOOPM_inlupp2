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
    ioopm_hash_table_t *items; // name -> cart_item
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

bool cart_add(cart_t *cart, db_t *db, char *name, size_t amount)
{
    // TOFIX: take other carts into account, ensure carts combined don't exceed database's stock!
    size_t ware_stock = 0;
    get_stock(db, name, &ware_stock);

    if (amount > ware_stock)
    {
        return false;
    }
    else
    {
        size_t prior_amount = 0;
        ioopm_hash_table_lookup(cart->items, PTR_AS_ELEM(name), &INT_AS_ELEM(prior_amount));
        ioopm_hash_table_insert(cart->items, PTR_AS_ELEM(name), INT_AS_ELEM(amount + prior_amount));
        return true;
    }
}

bool cart_remove(cart_t *cart, char *name, size_t amount)
{
    size_t old_amount;

    (void) old_amount;
    (void) cart;
    (void) name;
    (void) amount;

    return false;
}