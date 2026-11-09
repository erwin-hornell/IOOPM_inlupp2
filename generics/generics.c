#include <stdlib.h>
#include "generics.h"
#include <string.h>
#include "../utils/utils.h" // hashtable and list



struct item
{
    char *name;
    char *desc;
    int price;
};

item_t *item_create(char *name, char *desc, int price)
{
    item_t *item = calloc(1, sizeof(item_t));
    item->name = name;
    item->desc = desc;
    item->price = price;

    return item;
}

void item_destroy(item_t *item)
{
    free(item->name);
    free(item->desc);
    free(item);
}

char *item_name(item_t *item)
{
    return item->name;
}
char *item_desc(item_t *item)
{
    return item->desc;
} 
int item_price(item_t *item)
{
    return item->price;
}

void item_update_name(item_t *item, char* new_name)
{
    item->name = new_name;
}
void item_update_desc(item_t *item, char* new_desc)
{
    item->desc = new_desc;
}
void item_update_price(item_t *item, int new_price)
{
    item->price = new_price;
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



struct shelf
{
    char *name;
    size_t amount;
};

shelf_t *shelf_create(char *name, size_t amount)
{
    shelf_t *shelf = calloc(1, sizeof(shelf_t));
    shelf->name = name;
    shelf->amount = amount;
    return shelf;
}

void shelf_destroy(shelf_t *shelf)
{
    free(shelf->name);
    free(shelf);
}

char *shelf_name(shelf_t *shelf)
{
    return shelf->name;
}
size_t shelf_amount(shelf_t *shelf)
{
    return shelf->amount;
}
void shelf_amount_set(shelf_t *shelf, size_t amount) {
    shelf->amount = amount;
}
void shelf_amount_add(shelf_t *shelf, size_t addend) {
    shelf->amount += addend;
}
void shelf_amount_remove(shelf_t *shelf, size_t addend) {
    shelf->amount -= addend;
}


size_t int_hash(const value_t key)
{
  return key.i;
}

bool int_comp(const value_t a, const value_t b)
{
  return a.i == b.i;
}