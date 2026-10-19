// standard
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// header
#include "db.h"
#include "utils.h"
// hash table
#include "../IOOPM_inlupp1/hash_table.h"
#include "../IOOPM_inlupp1/hash_table_iterator.h"
// linked list
#include "../IOOPM_inlupp1/linked_list.h"
#include "../IOOPM_inlupp1/linked_list_iterator.h"

struct db_merch
{
    item_t *item;
    ioopm_list_t *locs;
};

typedef struct db_merch db_merch_t;

struct  shelf
{
    char *name;
    size_t amount;
};
typedef struct shelf shelf_t;


struct db
{
    ioopm_hash_table_t *merch; // name -> merch;
};

shelf_t *create_shelf(char *name, size_t amount)
{
    shelf_t *shelf = calloc(1, sizeof(shelf_t));
    shelf->name = name;
    shelf->amount = amount;
    return shelf;
}

void destroy_shelf(shelf_t *shelf)
{
    free(shelf->name);
    free(shelf);
}

void destroy_merch(db_merch_t *merch)
{
    destroy_item(merch->item);
    ioopm_list_iterator_t *it;
    for(it = ioopm_list_iterator_create(merch->locs);
        !ioopm_list_iterator_at_end(it);
        ioopm_list_iterator_advance(it))
        {
            shelf_t *shelf = ioopm_list_iterator_current(it).p;
            destroy_shelf(shelf);
        }
    ioopm_list_iterator_destroy(it);
    
    ioopm_list_destroy(merch->locs);
    free(merch);
}

db_t *create_db()
{
    db_t *db = calloc(1, sizeof(db_t));
    ioopm_hash_table_t *merch = ioopm_hash_table_create(str_hash, str_comp);
    db->merch = merch;
    return db;
    
}


void destroy_db(db_t *db)
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
    merch->item = create_item(name, desc, price);
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



bool edit_merch(db_t *db, char *name, char *new_name, char* new_desc, size_t new_price)
{
    value_t res, res2;
    //if the new name is taken by any merch other than the merch we want edit we fail.
    if(!ioopm_hash_table_lookup(db->merch, PTR_AS_ELEM(name), &res)
        ||(ioopm_hash_table_lookup(db->merch, PTR_AS_ELEM(new_name), &res2)
        && res.p != res2.p))
    {
        return false;
    }
    ioopm_hash_table_remove(db->merch, PTR_AS_ELEM(name), &res);
    db_merch_t *old_merch = res.p;
    destroy_merch(old_merch);
    add_merch(db, new_name, new_desc, new_price);
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
            if(strcmp(loc_name, shelf->name) == 0)
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
        shelf->amount += amount;
        return true;
    }
    shelf = create_shelf(strdup(loca), amount);
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
        stock += shelf->amount;
    }
    ioopm_list_iterator_destroy(it);
    *res = stock;
    return true;
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
