#include <stddef.h>
#include <stdlib.h>
#include "db.h"
//TODO: Fix path
#include "../IOOPM_inlupp1/hash_table.h"
#include "../IOOPM_inlupp1/hash_table_iterator.h"

#include "../IOOPM_inlupp1/linked_list.h"
#include "../IOOPM_inlupp1/linked_list_iterator.h"

struct item
{
    char *name;
    char *desc;
    int price;

};
typedef struct item item_t;

//TODO: Fix name
struct db_merch
{
    item_t *item;
    ioopm_list_t *locs;
};

typedef struct db_merch db_merch_t;

struct  shelf
{
    char *name;
    int amount;
};
typedef struct shelf shelf_t;


struct db
{
    ioopm_hash_table_t *merch; // name -> merch;
};

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
        ioopm_hash_table_iterator_at_end(it);
        ioopm_hash_table_iterator_advance(it))
        {
            db_merch_t *merch = (db_merch_t *) ioopm_hash_table_iterator_current_value(it).p;
            free(merch->item);
            ioopm_list_destroy(merch->locs);
        }
    ioopm_hash_table_iterator_destroy(it);
    free(db);

}