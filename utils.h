#pragma once

#include <stdlib.h>


typedef struct item item_t;

item_t *create_item(char *name, char *desc, int price);

void destroy_item(item_t *item);

char *item_name(item_t *item);
char *item_desc(item_t *item);
int item_price(item_t *item);