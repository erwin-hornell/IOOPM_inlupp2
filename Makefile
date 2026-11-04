CC = gcc

CFLAGS = -Wall -Wextra -g -I ../IOOPM_inlupp1
LDLIBS = -lcunit
VALGRIND = valgrind --leak-check=full
GDB = gdb

SHOP = db.c cart.c shop.c
PROF_DEST = ./tests/prof
TARGET_db = db_tests
TARGET_cart = cart_tests
TARGET_shop = shop_tests
TARGET_main = main
UTILS = utils/utils.c
STR_UTILS = utils/string_utils.c

GENERICS = ./generics/generics.c
TESTS_DB = tests/db_tests.c
TESTS_CART = tests/cart_tests.c
TESTS_SHOP = tests/shop_tests.c


IOOPM_SRC = ../IOOPM_inlupp1/hash_table.c ../IOOPM_inlupp1/linked_list.c

all: $(TARGET_db) $(TARGET_cart)

# Create destination folder
$(PROF_DEST):
	mkdir -p $(PROF_DEST)

# Database tests
$(TARGET_db): db.c $(TESTS_DB) $(IOOPM_SRC) $(GENERICS) | $(PROF_DEST)
	$(CC) $(CFLAGS) --coverage $^ -o $(PROF_DEST)/$@ $(LDLIBS)

tests-db: $(TARGET_db)
	./$(PROF_DEST)/$(TARGET_db)

valgrind-db: $(TARGET_db)
	$(VALGRIND) ./$(PROF_DEST)/$(TARGET_db)

# Cart tests
$(TARGET_cart): cart.c $(TESTS_CART) $(IOOPM_SRC) $(GENERICS) | $(PROF_DEST)
	$(CC) $(CFLAGS) --coverage $^ -o $(PROF_DEST)/$@ $(LDLIBS)

tests-cart: $(TARGET_cart)
	./$(PROF_DEST)/$(TARGET_cart)

valgrind-cart: $(TARGET_cart)
	$(VALGRIND) ./$(PROF_DEST)/$(TARGET_cart)

gdb-cart: $(TARGET_cart)
	$(GDB) ./$(PROF_DEST)/$(TARGET_cart)

# shop tests
$(TARGET_shop): $(SHOP) $(TESTS_SHOP) $(IOOPM_SRC) $(GENERICS) | $(PROF_DEST)
	$(CC) $(CFLAGS) --coverage $^ -o $(PROF_DEST)/$@ $(LDLIBS)

tests-shop: $(TARGET_shop)
	./$(PROF_DEST)/$(TARGET_shop)

valgrind-shop: $(TARGET_shop)
	$(VALGRIND) ./$(PROF_DEST)/$(TARGET_shop)

gdb-shop: $(TARGET_shop)
	$(GDB) ./$(PROF_DEST)/$(TARGET_shop)


$(TARGET_main): main.c user_UI.c $(SHOP) $(IOOPM_SRC) $(GENERICS) $(UTILS) $(STR_UTILS)
	$(CC) $^ -o ./src/main

run: $(TARGET_main)
	./src/main

valgrind-main: $(TARGET_main)
	$(VALGRIND) ./src/main

clean:
	rm -f $(TARGET_db) $(TARGET_cart) *.gcda *.gcno *.gcov
	rm -f $(PROF_DEST)/*
	rm -f src/*
	rm -f gmon.out profile.txt