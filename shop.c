#include <string.h>
#include <stdlib.h>

#include "cart.h"
#include "db.h"
#include "shop.h"
//TODO: Fix path
#include "hash_table.h"
#include "hash_table_iterator.h"
#include "linked_list.h"
#include "linked_list_iterator.h"

struct shop 
{
    db_t *db;
   ioopm_hash_table_t *carts; //should maybe be hash table
    size_t carts_id;
};

shop_t *shop_create()
{
    shop_t *shop = calloc(1, sizeof(shop_t));
    shop->db = create_db();
    shop->carts = ioopm_hash_table_create(int_hash, int_comp);
    shop->carts_id = 0;
    return shop;
}

void shop_destroy(shop_t *shop)
{
    ioopm_hash_table_iterator_t *it;
    for(it = ioopm_hash_table_iterator_create(shop->carts);
        !ioopm_hash_table_iterator_at_end(it);
        ioopm_hash_table_iterator_advance(it))
    {
        cart_t *cart = ioopm_hash_table_iterator_current_value(it).p;
        //key is int and does not need to be destroyed
        cart_destroy(cart);
    }
    ioopm_hash_table_iterator_destroy(it);

    ioopm_hash_table_destroy(shop->carts);
    db_destroy(shop->db);
    free(shop);
}

bool add_to_db(shop_t *shop, char *name, char *desc, size_t price)
{
    return add_merch(shop->db, name, desc, price);
}

bool edit_item(shop_t *shop, char *name, char *new_name, char *new_desc, size_t new_price)
{
    return edit_merch(shop->db, name, new_name, new_desc, new_price);
}

ioopm_list_t *list_db(shop_t *shop)
{
    return get_all_items(shop->db);
}

ioopm_list_t *get_merch_locs(shop_t *shop, char *name)
{
    ioopm_list_t *locs;
    get_locs(shop->db, name, &locs);
    return locs;
}

bool db_replenish(shop_t *shop, char *name, char *loc, size_t amount)
{
    return add_stock(shop->db, name, loc, amount);
}

void new_cart(shop_t *shop)
{
    cart_t *new_cart = cart_create(shop->carts_id);
    shop->carts_id++;
    ioopm_hash_table_insert(
            shop->carts, 
            INT_AS_ELEM(cart_id(new_cart)),
            PTR_AS_ELEM(new_cart));
}

// bool get_cart(shop_t *shop, size_t id, cart_t **res)
// {
//     ioopm_list_iterator_t *it;
//     for(it = ioopm_list_iterator_create(shop->carts);
//         !ioopm_list_iterator_at_end(it);
//         ioopm_list_iterator_advance(it))
//     {
//         cart_t *current = ioopm_list_iterator_current(it).p;
//         if(cart_id(current) == id)
//         {
//             ioopm_list_iterator_destroy(it);
//             *res = current;
//             return true;
//         }
//     }
//     ioopm_list_iterator_destroy(it);
//     return false;
// }

bool remove_cart(shop_t *shop, size_t id)
{
    return ioopm_hash_table_remove(shop->carts, INT_AS_ELEM(id), NULL);
}

bool add_to_cart(shop_t *shop, size_t id, item_t *item, size_t amount)
{


    value_t res;
    if(!ioopm_hash_table_lookup(shop->carts, INT_AS_ELEM(id), &res))
    {
        return false;
    }
    cart_t *cart = res.p;
    cart_add(cart, item, amount);
    return true;
}

bool add_to_cart(shop_t *shop, size_t id, item_t *item, size_t amount)
{
    value_t res;
    if(!ioopm_hash_table_lookup(shop->carts, INT_AS_ELEM(id), &res))
    {
        return false;
    }
    cart_t *cart = res.p;
    return cart_remove(cart, item, amount);
}

bool can_checkout(shop_t *shop, size_t id)
{
    value_t res;
    if(!ioopm_hash_table_lookup(shop->carts, INT_AS_ELEM(id), &res))
    {
        return 0;
    }
    cart_t *cart = res.p;


    ioopm_hash_table_iterator_t *it;
    for(it = ioopm_hash_table_iterator_create(cart);
        !ioopm_hash_table_iterator_at_end(it);
        ioopm_hash_table_iterator_advance(it))
    {
        cart_item_t *cart_item = ioopm_hash_table_iterator_current_value(it).p;
        char *name = item_name(cart_item_item(cart_item));
        size_t amount = cart_item_amount(cart_item);
        size_t amount_in_stock;
        if(!get_stock(shop->db, name, &amount_in_stock)
            || amount_in_stock < amount);
            {
                ioopm_hash_table_iterator_destroy(it);
                return false;
            }
    }
    ioopm_hash_table_iterator_destroy(it);
    return true;
}


bool checkout_cart(shop_t *shop, size_t id)
{
    value_t res;
    if(!ioopm_hash_table_lookup(shop->carts, INT_AS_ELEM(id), &res))
    {
        return 0;
    }
    if(!can_checkout(shop, id))
    {
        return false;
    }
    cart_t *cart = res.p;

    ioopm_hash_table_iterator_t *it;
    for(it = ioopm_hash_table_iterator_create(cart);
        !ioopm_hash_table_iterator_at_end(it);
        ioopm_hash_table_iterator_advance(it))
    {
        cart_item_t *cart_item = ioopm_hash_table_iterator_current_value(it).p;
        size_t amount_in_stock;
        if(!remove_stock(shop->db, 
                item_name(cart_item_item(cart_item)),
                cart_item_amount(cart_item)));
            {
                //should never be the case
                ioopm_hash_table_iterator_destroy(it);
                return false;
            }
    }
    ioopm_hash_table_iterator_destroy(it);
    return true;
}