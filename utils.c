#include <stdlib.h>
#include "utils.h"
// hash table
#include "../IOOPM_inlupp1/hash_table.h"
#include "../IOOPM_inlupp1/hash_table_iterator.h"
// linked list
#include "../IOOPM_inlupp1/linked_list.h"
#include "../IOOPM_inlupp1/linked_list_iterator.h"

struct item
{
    char *name;
    char *desc;
    int price;
};

item_t *create_item(char *name, char *desc, int price)
{
    item_t *item = calloc(1, sizeof(item_t));
    item->name = name;
    item->desc = desc;
    item->price = price;

    return item;
}

void destroy_item(item_t *item)
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