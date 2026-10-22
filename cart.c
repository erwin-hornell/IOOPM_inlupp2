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


/// @note does NOT destroy item_t, this is a cart_item_t!
void cart_item_destroy(cart_item_t *cart_item)
{
    free(cart_item);
}


cart_t *cart_create()
{
    cart_t *cart = calloc(1, sizeof(cart_t));
    cart->items = ioopm_hash_table_create(str_hash, str_comp);
    return cart;
}


void cart_destroy(cart_t *cart)
{
    // destroy cart_item_t:s (not the item_t:s used by database!!!)
    ioopm_hash_table_iterator_t *it;
    for (it = ioopm_hash_table_iterator_create(cart->items);
        !ioopm_hash_table_iterator_at_end(it);
        ioopm_hash_table_iterator_advance(it))
        {
            cart_item_t *cart_item = ioopm_hash_table_iterator_current_value(it).p;
            cart_item_destroy(cart_item);
        }
    ioopm_hash_table_iterator_destroy(it);

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


bool cart_remove(cart_t *cart, item_t *item, size_t amount)
{
    // lookup item
    value_t cart_item_v;
    if (!ioopm_hash_table_lookup(cart->items, PTR_AS_ELEM(item_name(item)), &cart_item_v))
    {
        // item was not present in cart
        return false;
    }

    // item type in cart
    cart_item_t *cart_item = cart_item_v.p;

    if (amount > cart_item->amount)
    { // we are trying to remove more than is in the cart
        return false;
    }
    else if (amount == cart_item->amount)
    { // we are removing the entire amount
        ioopm_hash_table_remove(cart->items, PTR_AS_ELEM(item_name(item)), &cart_item_v);
        cart_item_destroy(cart_item);
        return true;
    }
    else
    { // decrement cart's amount
        cart_item->amount -= amount;
        return true;
    }
}


size_t cart_amount(cart_t *cart, item_t *item)
{
    // lookup item
    value_t cart_item_v;
    if (ioopm_hash_table_lookup(cart->items, PTR_AS_ELEM(item_name(item)), &cart_item_v))
    { // item type already in cart
        cart_item_t *cart_item = cart_item_v.p;
        return cart_item->amount;
    }
    else
    { // item type not already in cart
        return 0;
    }
}


void insert_in_order(item_t *to_insert, ioopm_list_t *list)
{
    if(ioopm_list_is_empty(list))
    {
        ioopm_list_append(list, PTR_AS_ELEM(to_insert));
        return;
    }
    ioopm_list_iterator_t *list_it;

    for(list_it = ioopm_list_iterator_create(list);
        !ioopm_list_iterator_at_end(list_it);
        ioopm_list_iterator_advance(list_it))
        {
            item_t *current_merch = ioopm_list_iterator_current(list_it).p;
            if(strcmp(item_name(to_insert), item_name(current_merch)) < 0)
            {
                ioopm_list_iterator_insert(list_it, PTR_AS_ELEM(to_insert));
                ioopm_list_iterator_destroy(list_it);
                return;
            }

        }
    ioopm_list_append(list, PTR_AS_ELEM(to_insert));
    ioopm_list_iterator_destroy(list_it);
}

ioopm_list_t *cart_items(cart_t *cart)
{
    ioopm_list_t *ls = ioopm_list_create();

    ioopm_hash_table_iterator_t *it;
    for (it = ioopm_hash_table_iterator_create(cart->items);
        !ioopm_hash_table_iterator_at_end(it);
        ioopm_hash_table_iterator_advance(it))
        {
            cart_item_t *cart_item = ioopm_hash_table_iterator_current_value(it).p;
            insert_in_order(cart_item, ls);
        }
    ioopm_hash_table_iterator_destroy(it);

    return ls;
}