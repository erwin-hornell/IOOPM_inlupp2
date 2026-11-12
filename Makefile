CC = gcc

CFLAGS = -Wall -Wextra -g -O0 -I --coverage
LDLIBS = -lcunit
VALGRIND = valgrind --leak-check=full
GDB = gdb
GCOV = gcov
COVERAGE = gcovr


BACKEND = backend/db.c backend/cart.c backend/shop.c
PROF_DEST = tests/prof
TARGET_db = db_tests
TARGET_cart = cart_tests
TARGET_shop = shop_tests
TARGET_main = main
UTILS = utils/utils.c
STR_UTILS = utils/string_utils.c

GENERICS = generics/generics.c
TESTS_DB = tests/db_tests.c
TESTS_CART = tests/cart_tests.c
TESTS_SHOP = tests/shop_tests.c


IOOPM_SRC = utils/list_structs/hash_table.c utils/list_structs/linked_list.c

all: $(TARGET_db) $(TARGET_cart) $(TARGET_shop) $(TARGET_main)

# Create destination folder
$(PROF_DEST):
	mkdir -p $(PROF_DEST)

# Database tests
$(TARGET_db): backend/db.c $(TESTS_DB) $(IOOPM_SRC) $(GENERICS) | $(PROF_DEST)
	$(CC) $(CFLAGS) --coverage $^ -o $(PROF_DEST)/$@ $(LDLIBS)

tests-db: $(TARGET_db)
	./$(PROF_DEST)/$(TARGET_db)

valgrind-db: $(TARGET_db)
	$(VALGRIND) ./$(PROF_DEST)/$(TARGET_db)

gdb-db: $(TARGET_db)
	$(GDB) ./$(PROF_DEST)/$(TARGET_db)


# Cart tests
$(TARGET_cart): backend/cart.c $(TESTS_CART) $(IOOPM_SRC) $(GENERICS) | $(PROF_DEST)
	$(CC) $(CFLAGS) --coverage $^ -o $(PROF_DEST)/$@ $(LDLIBS)

tests-cart: $(TARGET_cart)
	./$(PROF_DEST)/$(TARGET_cart)

valgrind-cart: $(TARGET_cart)
	$(VALGRIND) ./$(PROF_DEST)/$(TARGET_cart)

gdb-cart: $(TARGET_cart)
	$(GDB) ./$(PROF_DEST)/$(TARGET_cart)



# shop tests
$(TARGET_shop): $(BACKEND) $(TESTS_SHOP) $(IOOPM_SRC) $(GENERICS) | $(PROF_DEST)
	$(CC) $(CFLAGS) --coverage $^ -o $(PROF_DEST)/$@ $(LDLIBS)

tests-shop: $(TARGET_shop)
	./$(PROF_DEST)/$(TARGET_shop)

valgrind-shop: $(TARGET_shop)
	$(VALGRIND) ./$(PROF_DEST)/$(TARGET_shop)

gdb-shop: $(TARGET_shop)
	$(GDB) ./$(PROF_DEST)/$(TARGET_shop)


$(TARGET_main): main.c frontend/user_UI.c $(BACKEND) $(IOOPM_SRC) $(GENERICS) $(UTILS) $(STR_UTILS)
	$(CC) $^ -o ./src/main

run: $(TARGET_main)
	./src/main

valgrind-main: $(TARGET_main)
	$(VALGRIND) ./src/main

valgrind-text: $(TARGET_main)
	$(VALGRIND) ./src/main < test.txt
	
gdb-main: $(TARGET_main)
	$(GDB) ./src/main




# Database coverage

gcov-db: tests-db
	./$(PROF_DEST)/$(TARGET_db)
	gcovr --root . --object-directory $(PROF_DEST) --filter 'backend/db.c' --txt

# Cart coverage
gcov-cart: tests-cart
	./$(PROF_DEST)/$(TARGET_cart)
	gcovr --root . --object-directory $(PROF_DEST) --filter 'backend/cart.c' --txt


# Shop coverage
gcov-shop: tests-shop
	./$(PROF_DEST)/$(TARGET_shop)
	gcovr --root . --object-directory $(PROF_DEST) --filter 'backend/shop.c' --txt


clean:
	rm -f $(TARGET_db) $(TARGET_cart) *.gcda *.gcno *.gcov
	rm -f $(PROF_DEST)/*
	rm -f src/*
	rm -f gmon.out profile.txt