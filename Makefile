CC = gcc

CFLAGS = -Wall -Wextra -g -I../IOOPM_inlupp1
LDLIBS = -lcunit
VALGRIND = valgrind --leak-check=full
GDB = gdb

TARGET_db = db-tests
TARGET_cart = cart-tests

TESTS_DB = tests/db_tests.c
TESTS_CART = tests/cart_tests.c

IOOPM_SRC = ../IOOPM_inlupp1/hash_table.c \
	../IOOPM_inlupp1/linked_list.c

all: $(TARGET_db)

# Database tests
$(TARGET_db): db.c $(TESTS_DB) $(IOOPM_SRC) utils.c
	$(CC) $(CFLAGS) --coverage $^ -o $@ $(LDLIBS)

tests-db: $(TARGET_db)
	./$(TARGET_db)

valgrind-db: $(TARGET_db)
	$(VALGRIND) ./$(TARGET_db)

# Cart tests
$(TARGET_cart): db.c $(TESTS_CART) $(IOOPM_SRC) utils.c
	$(CC) $(CFLAGS) --coverage $^ -o $@ $(LDLIBS)

tests-cart: $(TARGET_cart)
	./$(TARGET_cart)

valgrind-cart: $(TARGET_cart)
	$(VALGRIND) ./$(TARGET_cart)

gdb-cart: $(TARGET_cart)
	$(GDB) ./$(TARGET_cart)

clean:
	rm -f $(TARGET_db) $(TARGET_cart) *.gcda *.gcno *.gcov
	rm -f gmon.out profile.txt

#######################
##### LEOS PÅHITT #####
#######################

# Silent test database: valgrind + silent clean
stestdb:
	@$(MAKE) --no-print-directory -s clean
	@$(MAKE) --no-print-directory valgrind-db
	@$(MAKE) --no-print-directory -s clean

# Silent test cart: valgrind + silent clean
stestct:
	@$(MAKE) --no-print-directory -s clean
	@$(MAKE) --no-print-directory valgrind-cart
	@$(MAKE) --no-print-directory -s clean

.PHONY: all clean tests-db valgrind-db tests-cart valgrind-cart stestdb stestcart
