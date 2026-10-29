#include "shop.h"
#include "utils/utils.h"
#include "utils/string_utils.h"

#include "string.h"

int main()
{
    char option;
    bool end = false;
    shop_t *shop = shop_create();
    do{
        option = menu_main();
        switch (option)
        {
        case 'A':
            menu_add_item(shop);
            break;

        case 'L':
            menu_list_items(shop);
            break;

        case 'D':
            menu_remove_item(shop);
            break;

        case 'E':
            menu_edit_item(shop);
            break;

        case 'S':
            menu_show_stock(shop);
            break;

        case 'P':
            menu_replenish(shop);
            break;

        case 'C':
            menu_cart_create(shop);
            break;
            
        case 'R':
            menu_cart_remove(shop);
            break;

        case '+':
            menu_cart_add_item(shop);
            break;

        case '-':
            menu_cart_remove_item(shop);
            break;

        case '=':
            menu_cart_cost(shop);
            break;

        case 'O':
            menu_cart_checkout(shop);
            break;

        case 'U':
            menu_undo(shop);
            break;

        case 'F':
            menu_save(shop);
            break;

        case 'G':
            menu_save(shop);
            break;

        case 'Q':
            end_menu(shop, &end);
            break;
        
        default:
            break;
        }
    }while(!end);
}