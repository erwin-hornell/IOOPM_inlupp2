#pragma once

typedef struct item item_t;

/// @brief creates an item
/// @param name the item's name
/// @param desc the item's description
/// @param price the item's price in SEK
/// @return item pointer
item_t *create_item(char *name, char *desc, int price);

/// @brief destroys an item, freeing its memory
/// @param item an item
void destroy_item(item_t *item);

/// @brief gets the name of an item struct
/// @param item the item
/// @return the item's name
char *item_name(item_t *item);

/// @brief gets the description of an item struct
/// @param item the item
/// @return the item's description
char *item_desc(item_t *item);

/// @brief gets the price of an item struct
/// @param item the item
/// @return the item's price in SEK
int item_price(item_t *item);
