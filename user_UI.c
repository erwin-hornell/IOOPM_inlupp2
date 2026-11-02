#include <string.h>
#include <stdio.h>
#include "utils/utils.h"
#include "utils/string_utils.h"
#include "shop.h"


void start_menu(char *header)
{
    char buff[255];
    for(int i = 0; i < strlen(header)+2*9; i++)
    {
        buff[i] = '-';
    }
    buff[strlen(buff)-1] = '\0';
    printf("\n\n"
            "%s\n"
            "\t %s\n"
            "%s\n",
            buff,
            header,
            buff);
}

void print_suc(bool suc)
{
    if(suc)
    {
        printf("SUCCESS");
    }
    else
    {
        printf("FAILED");
    }
}

void print_items(ioopm_list_t *items)
{
    int index = 1;
    ioopm_list_iterator_t *it;
    for(it = ioopm_list_iterator_create(items);
        !ioopm_list_iterator_at_end(it);
        ioopm_list_iterator_advance(it))
        {
            item_t *item = ioopm_list_iterator_current(it).p;
            printf("%d: name: %s \t desc: %s \t price: %d\n",
                    index,
                    item_name(item),
                    item_desc(item),
                    item_price(item));
            index++;
        }
    ioopm_list_iterator_destroy(it);
}

char menu_main(shop_t *shop)
{
    start_menu("MAIN MENY");
    char option = ask_question_char("        \n"
                        "A - Add item to db     \n"
                        "L - List db items      \n"
                        "D - Remove item from db\n"
                        "E - Edit db item       \n"
                        "S - Show stock         \n"
                        "P - Replenish stock    \n"
                        "C - Create new cart    \n"
                        "R - Remove cart        \n"
                        "+ - Add to car         \n"
                        "- - Remove from cart   \n"
                        "= - Cart cost          \n"
                        "O - Cart checkout      \n"
                        "Z - Undo               \n"
                        "F - Save to file       \n"
                        "G - Load from file     \n"
                        "Q - Quit               \n");
    return option;
}

void menu_add_item(shop_t *shop)
{
    start_menu("ADD ITEM");
    char *name = ask_question_string("name: ");
    char *desc = ask_question_string("description: ");
    int price = ask_question_int("price: ");
    print_suc(add_to_db(shop, name, desc, price));


    
}

void menu_remove_item(shop_t *shop)
{
    start_menu("REMOVE ITEM");
    ioopm_list_t *items = list_db(shop);
    print_items(items);
    int index = ask_question_int("Selcet index: ");
    item_t *item = ioopm_list_get(items, index - 1).p;
    print_suc(remove_from_db(shop, item_name(item)));
}
void menu_edit_item(shop_t *shop)
{
    start_menu("EDIT ITEM");
    ioopm_list_t *items = list_db(shop);
    print_items(items);
    int index = ask_question_int("Selcet index: ");
    item_t *item = ioopm_list_get(items, index - 1).p;
    char *new_name = ask_question_string("new name: ");
    char *new_desc = ask_question_string("new description: ");
    int new_price = ask_question_int("new price: ");


    print_suc(edit_item(shop, item_name(item), new_name, new_desc, new_price));
}
void menu_list_items(shop_t *shop)
{
    start_menu("LIST ITEM");
    ioopm_list_t *items = list_db(shop);
    print_items(items);
}
void menu_show_stock(shop_t *shop)
{
    
}
void menu_replenish(shop_t *shop)
{
    
}
void menu_cart_create(shop_t *shop)
{
    
}
void menu_cart_remove(shop_t *shop)
{
    
}
void menu_cart_add_item(shop_t *shop)
{
    
}
void menu_cart_remove_item(shop_t *shop)
{
    
}
void menu_cart_cost(shop_t *shop)
{
    
}
void menu_cart_checkout(shop_t *shop)
{
    
}
void menu_undo(shop_t *shop)
{
    
}
void menu_save(shop_t *shop)
{
    
}
void menu_load(shop_t *shop)
{
    
}



void user_ui(shop_t *shop)
{
    char option;
    bool end = false;
    do{
        option = menu_main(shop);
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

/*         case 'S':
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

        case 'Z':
            menu_undo(shop);
            break;

        case 'F':
            menu_save(shop);
            break;

        case 'G':
            menu_load(shop);
            break; */

        case 'Q':
            end = true;
            break;
        
        default:
            break;
        }
    }while(!end);
}