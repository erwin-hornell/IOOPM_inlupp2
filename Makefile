CC = gcc

CFLAGS = -Wall -Wextra -g -I../IOOPM_inlupp1
LDLIBS = -lcunit
VALGRIND = valgrind
TARGET_db = db-tests
TESTS = tests/db_tests.c
IOOPM_SRC = ../IOOPM_inlupp1/hash_table.c \
	../IOOPM_inlupp1/linked_list.c \

all: $(TARGET_db)

$(TARGET_db): db.c $(TESTS) $(IOOPM_SRC)
	$(CC) $(CFLAGS) --coverage db.c $(TESTS) $(IOOPM_SRC) -o $@ $(LDLIBS)

tests-db: $(TARGET_db)
	./$(TARGET_db)

valgrind-db: $(TARGET_db)
	$(VALGRIND) ./$(TARGET_db)
clean:
	rm -f $(TARGET_db) *.gcda *.gcno *.gcov
	rm -f gmon.out profile.txt

.PHONY: all clean