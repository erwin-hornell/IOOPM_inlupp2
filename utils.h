#pragma once

#include <stdlib.h>

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