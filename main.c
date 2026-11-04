#include "shop.h"
#include "user_UI.h"

int main()
{
    shop_t *shop = shop_create();
    user_ui(shop);
    shop_destroy(shop);

}