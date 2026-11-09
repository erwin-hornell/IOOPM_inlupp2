#include "backend/shop.h"
#include "frontend/user_UI.h"

int main()
{
    shop_t *shop = shop_create();
    user_ui(shop);
    shop_destroy(shop);

}