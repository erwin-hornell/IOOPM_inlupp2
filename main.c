#include "shop.h"
#include "utils/utils.h"
#include "utils/string_utils.h"

#include "string.h"
#include "user_UI.h"

int main()
{
    shop_t *shop = shop_create();
    user_ui(shop);

}