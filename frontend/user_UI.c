#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../utils/utils.h"
#include "../utils/string_utils.h"
#include "../backend/shop.h"
#include <stdlib.h>

#define MAX_PRINT 20

void new_menu(char *header)
{
    int len = strlen(header)+(2*9);
    char buff[len];
    for(int i = 0; i < len; i++)
    {
        buff[i] = '-';
    }
    printf("\n\n"
            "%.*s\n"
            "\t %s\n"
            "%.*s\n",
            len, buff,
            header,
            len, buff);
}

bool is_shelf(char *str)
{
    return isupper((unsigned char)str[0]) &&
           isdigit((unsigned char)str[1]) &&
           isdigit((unsigned char)str[2]) &&
           str[3] == '\0';
}

char *ask_question_shelf(char *question){
    return ask_question(question, is_shelf, (convert_func *)strdup).string_value;
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

bool confirm(char *question)
{
    char ans = ask_question_char(question);
    return toupper(ans) == 'Y';
}

int print_items(ioopm_list_t *items)
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

            if(index % MAX_PRINT == 0)
            {
                char next = ask_question_char(
                    "Press any to continue listing or n/N to return: ");
                if(toupper(next) == 'N')
                {
                    ioopm_list_iterator_destroy(it);
                    return index;
                }
            }
            
            index++;
        }
    ioopm_list_iterator_destroy(it);
    if(index == 1)
    {
        printf("No items in database");
    }
    return index;
}

int print_carts(ioopm_list_t *carts)
{
    int index = 1;
    ioopm_list_iterator_t *it;
    for(it = ioopm_list_iterator_create(carts);
        !ioopm_list_iterator_at_end(it);
        ioopm_list_iterator_advance(it))
        {
            int id = ioopm_list_iterator_current(it).i;
            printf("%d: cart_%d \n",
                    id,
                    id);
            index++;
        }
    ioopm_list_iterator_destroy(it);
    if(index == 1)
    {
        printf("No carts in shop");
    }
    return index;
}


void print_locations(ioopm_list_t *locs, char *name)
{
    int index = 1;

    printf("Stock of %s: \n", name);

    ioopm_list_iterator_t *it;
    for(it = ioopm_list_iterator_create(locs);
        !ioopm_list_iterator_at_end(it);
        ioopm_list_iterator_advance(it))
        {
            shelf_t *shelf = ioopm_list_iterator_current(it).p;
            printf("%d: shelf: %s \t amount: %d \n",
                    index,
                    shelf_name(shelf),
                    (int)shelf_amount(shelf));
            index++;
        }
    ioopm_list_iterator_destroy(it);
    if(index == 1)
    {
        printf("Item not in stock");
    }
}

bool try_ask_item(shop_t *shop, char **name)
{
    ioopm_list_t *items = list_db(shop);
    print_items(items);
    *name = ask_question_string("Enter name of item: ");
    ioopm_list_destroy(items);
    return true;
}

bool try_ask_cart(shop_t *shop, int *id)
{
    ioopm_list_t *carts = get_carts(shop);
    print_carts(carts);
    *id = ask_question_int("Select id of cart: ");

    ioopm_list_destroy(carts);

    return true;
    
}




char menu_main(shop_t *shop)
{
    new_menu("MAIN MENY");
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
    new_menu("ADD ITEM");
    char *name = ask_question_string("name: "); // uses strdup
    char *desc = ask_question_string("description: ");// uses strdup
    int price = ask_question_int("price: ");
    print_suc(add_to_db(shop, name, desc, price));
    free(name);
    free(desc);

    
}

void menu_remove_item(shop_t *shop)
{
    new_menu("REMOVE ITEM");
    char *name;
    if(!try_ask_item(shop, &name))
    {
        return;
    }
    if(!confirm("Are you sure you want to remove item? (Y/N):"))
    {
        free(name);
        return;
    }
    print_suc(remove_from_db(shop, name));
    free(name);
}
void menu_edit_item(shop_t *shop)
{
    new_menu("EDIT ITEM");
    char *name;
    if(!try_ask_item(shop, &name))
    {
        return;
    }
    char *new_name = ask_question_string("new name: "); // uses strdup
    char *new_desc = ask_question_string("new description: ");// uses strdup
    int new_price = ask_question_int("new price: ");

    if(!confirm("Are you sure you want to edit item? (Y/N):"))
    {
        free(new_name);
        free(new_desc);
        free(name);
        return;
    }

    print_suc(edit_item(shop, name, new_name, new_desc, new_price));
    free(new_name);
    free(new_desc);
    free(name);

}
void menu_list_items(shop_t *shop)
{
    new_menu("LIST ITEM");
    ioopm_list_t *items = list_db(shop);
    print_items(items);
    ioopm_list_destroy(items);
}
void menu_show_stock(shop_t *shop)
{
    new_menu("SHOW STOCK");
    char *name;
    if(!try_ask_item(shop, &name))
    {
        return;
    }
    ioopm_list_t *locs;
    if(!get_merch_locs(shop, name, &locs))
    {
        printf("Could not find locations of item: %s" , name);
        free(name);
        return;
    }
    print_locations(locs, name);
    free(name);
}
void menu_replenish(shop_t *shop)
{
    new_menu("REPLENISH STOCK");

    char *loc = ask_question_shelf("Enter shelf: ");

    char *name;
    if(!try_ask_item(shop, &name))
    {
        free(loc);
        return;
    }

    printf("Adding stock to %s:\n", name);

    int amount = ask_question_int("Enter amount: ");

    print_suc(db_replenish(shop, name, loc, amount));
    free(name);
    free(loc);
}
void menu_cart_create(shop_t *shop)
{
    new_cart(shop);
}
void menu_cart_remove(shop_t *shop)
{
    new_menu("REMOVE CART");
    int cart_id = 0;
    if(!try_ask_cart(shop, &cart_id))
    {
        return;
    }
    if(!confirm("Are you sure you want to remove the cart? (Y/N):"))
    {
        return;
    }
    print_suc(remove_cart(shop, cart_id));
}
void menu_cart_add_item(shop_t *shop)
{
    new_menu("ADD ITEM TO CART");
    int cart_id = 0;

    if(!try_ask_cart(shop, &cart_id))
        return;

    char *name;

    if(!try_ask_item(shop, &name))
        return;

    size_t amount = (size_t)ask_question_int("Enter amount to add: ");
    print_suc(add_to_cart(shop, cart_id, name, amount));
    free(name);
}
void menu_cart_remove_item(shop_t *shop)
{
    new_menu("REOMVE ITEM FROM CART");
    int cart_id = 0;

    if(!try_ask_cart(shop, &cart_id))
        return;

    char *name;

    if(!try_ask_item(shop, &name))
        return;

    int amount = ask_question_int("Enter amount to remove: ");
    print_suc(remove_from_cart(shop, cart_id, name, amount));
    free(name);
}
void menu_cart_cost(shop_t *shop)
{
    new_menu("TOTAL PRICE OF CART");
    int cart_id = 0;

    if(!try_ask_cart(shop, &cart_id))
        return;

    size_t total_cost;
    if(! cart_total_cost(shop, cart_id, &total_cost))
    {
        printf("Somthing went wrong\n");
        return;
    }
    printf("The total cost of cart_%d: %d", cart_id, (int)total_cost);

}
void menu_cart_checkout(shop_t *shop)
{
    new_menu("CHECKOUT CART");
    int cart_id = 0;

    if(!try_ask_cart(shop, &cart_id))
        return;

    print_suc(checkout_cart(shop, cart_id));

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
        option = toupper(menu_main(shop));
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
/* TODO: implement
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
            end = confirm("Are you sure you want to end? (Y/N): ");
            break;
        
        default:
            break;
        }
    }while(!end);
}