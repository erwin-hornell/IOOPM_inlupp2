## Inlupp 1

Inlupp 1 is a C library created as part of the course Imperativ och objektorienterad programmeringsmetodik (1DL221), HT2026.

# The project contains:

A shop system for an online store, which allows adding/editing items in a database, setting their stock, creating shopping carts, and checking out said carts (the system ensures the cart order can be satisfied and depletes stock). Created by Erwin Hörnell and Leonard Öhrström.

# Requirements

The project requires:

* GCC
* Make
* CUnit
* Valgrind (for memory checking)
* gcovr (for coverage)

# Running
User Interface

To run the user interface:
```bash
make run
```

Alternatively, for running with Valgrind:
```bash
make valgrind-main
```

Or running with GDB:
```bash
make gdb-main
```



Tests

Run an example textfile as input for the user interface with Valgrind:
```bash
make valgrind-text
```

Run the database test suite:
```bash
make tests-db
```

Run the cart test suite:

```bash
make tests-cart
```

Run the shop test suite:

```bash
make tests-shop
```

Valgrind Tests

Run the database test suite with Valgrind:
```bash
make valgrind-db
```

Run the cart test suite with Valgrind:

```bash
make tests-cart
```

Run the shop test suite with Valgrind:

```bash
make tests-shop
```

Code Coverage

Generate coverage information for the database test suite:

```bash
make gcov-db
```

Generate coverage information for the cart test suite:

```bash
make gcov-cart
```

Generate coverage information for the shop test suite:

```bash
make gcov-shop
```

# Coverage
| FILE          | Lines     | Line Exec   | Line Cover | 
| ------------- | --------- | ----------- | ---------- |
| db.c          | 132       | 125         | 94%        |
| cart.c        | 80        | 80          | 100%       |
| shop.c        | 142       | 138         | 97%        |
| TOTAL         | 354       | 343         | 97%        |

Data is from gcovr, see Run section for information on how to run.
 
# Design choices



# Cleaning generated files

To remove compiled binaries and generated coverage/profiling files:

```bash
make clean
```
