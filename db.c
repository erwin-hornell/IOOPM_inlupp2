#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"
#include "generics/generics.h"
//TODO: Fix path
#include "hash_table.h"
#include "hash_table_iterator.h"
#include "linked_list.h"
#include "linked_list_iterator.h"



//TODO: Fix name
struct db_merch
{
    item_t *item;
    ioopm_list_t *locs; // list of shelf_t
};

typedef struct db_merch db_merch_t;


struct db
{
    ioopm_hash_table_t *merch; // name -> merch;
};

void destroy_merch(db_merch_t *merch)
{
    
    item_destroy(merch->item);
    ioopm_list_iterator_t *it;
    for(it = ioopm_list_iterator_create(merch->locs);
        !ioopm_list_iterator_at_end(it);
        ioopm_list_iterator_advance(it))
        {
            shelf_t *shelf = ioopm_list_iterator_current(it).p;
            shelf_destroy(shelf);
        }
    ioopm_list_iterator_destroy(it);
    
    ioopm_list_destroy(merch->locs);
    free(merch);
}

db_t *db_create()
{
    db_t *db = calloc(1, sizeof(db_t));
    ioopm_hash_table_t *merch = ioopm_hash_table_create(str_hash, str_comp);
    db->merch = merch;
    return db;
    
}


void db_destroy(db_t *db)
{
    ioopm_hash_table_iterator_t *it;
    for(it = ioopm_hash_table_iterator_create(db->merch);
        !ioopm_hash_table_iterator_at_end(it);
        ioopm_hash_table_iterator_advance(it))
        {   
            db_merch_t *merch = (db_merch_t *) ioopm_hash_table_iterator_current_value(it).p;
            destroy_merch(merch);
        }
    ioopm_hash_table_iterator_destroy(it);
    ioopm_hash_table_destroy(db->merch);
    free(db);
}


db_merch_t *create_merch(char *name, char *desc, int price)
{
    db_merch_t *merch = calloc(1, sizeof(db_merch_t));
    merch->item = item_create(name, desc, price);
    merch->locs = ioopm_list_create();
    return merch;
}




bool add_merch(db_t *db, char *name, char *desc, int price)
{
    if(ioopm_hash_table_has_key(db->merch, PTR_AS_ELEM(name)))
    {
        return false;
    }
    db_merch_t *merch = create_merch(strdup(name), strdup(desc), price);
    ioopm_hash_table_insert(db->merch, PTR_AS_ELEM(item_name(merch->item)), PTR_AS_ELEM(merch));
    return true;
}

bool remove_merch(db_t *db, char *name)
{
    value_t res; 
    if(!ioopm_hash_table_remove(db->merch, PTR_AS_ELEM(name), &res))
    {
        return false;
    }
    destroy_merch(res.p);
    return true;
}

bool edit_merch(db_t *db, char *name, char* new_name, char *new_desc, size_t new_price)
{
    value_t old;
    value_t updated; 
    if(!ioopm_hash_table_lookup(db->merch, PTR_AS_ELEM(name), &old))
    {
        return false;
    }
    if(ioopm_hash_table_lookup(db->merch, PTR_AS_ELEM(new_name), &updated)
        && old.p != updated.p)
    {
        return false;
    }
    if(!ioopm_hash_table_remove(db->merch, PTR_AS_ELEM(name), &old))
    {
        return false;
    }
    //update without destroing or moving item means shopping carts dont need to be updated
    db_merch_t *to_update = old.p;
    free(item_name(to_update->item));
    free(item_desc(to_update->item));
    item_update_name(to_update->item, strdup(new_name));
    item_update_desc(to_update->item, strdup(new_desc));
    item_update_price(to_update->item, new_price);

    ioopm_hash_table_insert(db->merch,
                            PTR_AS_ELEM(item_name(to_update->item)),
                            PTR_AS_ELEM(to_update));
    return true;
}

bool get_merch(db_t *db, char *name, item_t **item)
{
    value_t res;
    if(!ioopm_hash_table_lookup(db->merch, PTR_AS_ELEM(name), &res))
    {
        return false;
    }
    db_merch_t *merch = res.p;
    *item = merch->item;
    return true;
}

bool is_on_shelf(db_merch_t *merch, char *loc_name, shelf_t **res)
{
    ioopm_list_iterator_t *it;
    for(it = ioopm_list_iterator_create(merch->locs);
        !ioopm_list_iterator_at_end(it);
        ioopm_list_iterator_advance(it))
        {
            shelf_t *shelf = ioopm_list_iterator_current(it).p;
            if(strcmp(loc_name, shelf_name(shelf)) == 0)
            {
                ioopm_list_iterator_destroy(it);
                *res = shelf;
                return true;
            }
        }
    ioopm_list_iterator_destroy(it);
    return false;
}


bool add_stock(db_t *db, char *name, char *loca, size_t amount)
{
    value_t res;
    if(!ioopm_hash_table_lookup(db->merch, PTR_AS_ELEM(name), &res))
    {
        return false;
    }
    db_merch_t *merch = res.p;
    shelf_t *shelf;
    if(is_on_shelf(merch, loca, &shelf))
    {
        shelf_amount_add(shelf, amount);
        return true;
    }
    shelf = shelf_create(strdup(loca), amount);
    ioopm_list_append(merch->locs, PTR_AS_ELEM(shelf));
    return true;
}

// takes db name of merch and returns sets locs to the relevents merch's list of locations
bool get_locs(db_t *db, char *name, ioopm_list_t **locs)
{
    value_t res;
    if(!ioopm_hash_table_lookup(db->merch, PTR_AS_ELEM(name), &res))
    {
        return false;
    }
    *locs = ((db_merch_t *) res.p)->locs;
    return true;
}

//given a db and name of merch sets res to the total amount of that merch
bool get_stock(db_t *db, char *name, size_t *res)
{
    ioopm_list_t *locs;
    if(!get_locs(db, name, &locs))
    {
        return false;
    }
    size_t stock = 0;
    ioopm_list_iterator_t *it;
    for(it = ioopm_list_iterator_create(locs);
        !ioopm_list_iterator_at_end(it);
        ioopm_list_iterator_advance(it))
    {
        shelf_t *shelf = ioopm_list_iterator_current(it).p;
        stock += shelf_amount(shelf);
    }
    ioopm_list_iterator_destroy(it);
    *res = stock;
    return true;
}
//loops locs twice
bool remove_stock(db_t *db, char *name, size_t amount)
{
    value_t res;
    if(!ioopm_hash_table_lookup(db->merch, PTR_AS_ELEM(name), &res))
    {
        return false;
    }
    db_merch_t *merch = res.p;
    size_t amount_in_stock;

    get_stock(db, name, &amount_in_stock);

    if(amount_in_stock < amount)
    {
        return false;
    }

    ioopm_list_iterator_t *it;
    for(it = ioopm_list_iterator_create(merch->locs);
        !ioopm_list_iterator_at_end(it);
        ioopm_list_iterator_advance(it))
    {
        shelf_t *shelf = ioopm_list_iterator_current(it).p;
        if(shelf_amount(shelf) > amount)
        {
            shelf_amount_add(shelf, -amount);
        }
        else
        {
            amount -= shelf_amount(shelf);
            ioopm_list_iterator_remove(it);
        }
    }
    return true;
}

ioopm_list_t *get_all_items(db_t *db)
{
    ioopm_list_t *res_list = ioopm_list_create();
    ioopm_hash_table_iterator_t *hash_it;
    for(hash_it = ioopm_hash_table_iterator_create(db->merch);
        !ioopm_hash_table_iterator_at_end(hash_it);
        ioopm_hash_table_iterator_advance(hash_it))
        {
            db_merch_t *to_insert = ioopm_hash_table_iterator_current_value(hash_it).p;
            insert_in_order(to_insert->item, res_list);
        }
        ioopm_hash_table_iterator_destroy(hash_it);
        return res_list;
}