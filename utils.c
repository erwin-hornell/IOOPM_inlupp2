#include <stdlib.h>

#include "utils.h"

struct item
{
    char *name;
    char *desc;
    int price;
};

typedef struct item item_t;

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