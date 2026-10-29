CC = gcc

CFLAGS = -Wall -Wextra -g -I ../IOOPM_inlupp1
LDLIBS = -lcunit
VALGRIND = valgrind --leak-check=full
GDB = gdb

PROF_DEST = ./tests/prof
TARGET_db = db_tests
TARGET_cart = cart_tests
UTILS = utils/utils.c
STR_UTILS = utils/string_utils.c
GENERICS = ./generics/generics.c
TESTS_DB = tests/db_tests.c
TESTS_CART = tests/cart_tests.c

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

clean:
	rm -f $(TARGET_db) $(TARGET_cart) *.gcda *.gcno *.gcov
	rm -f $(PROF_DEST)/*
	rm -f gmon.out profile.txt