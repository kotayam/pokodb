CC = gcc
CFLAGS = -Wall -Wextra -Og -ggdb3 -g

GDB = gdb

VALGRIND = valgrind
LOGDIR = log
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all
VALGRIND_OUTPUT = --log-file=$(LOGDIR)/log.txt
VALGRIND_OUTPUT_TEST = --log-file=$(LOGDIR)/log_test.txt

BUILDDIR = build
SRCDIR = src
INCLUDEDIR = include
TESTDIR = test

# src
MAIN = $(BUILDDIR)/main.o

_OBJ = hashmap.o
OBJ = $(patsubst %, $(BUILDDIR)/%, $(_OBJ)) 

_SRC = main.c hashmap.c
SRC = $(patsubst %, $(SRCDIR)/%, $(_SRC))

_DEPS = hashmap.h errors.h
DEPS = $(patsubst %, $(INCLUDEDIR)/%, $(_DEPS))

# test
_TEST_OBJ = main_test.o hashmap_test.o 
TEST_OBJ = $(patsubst %, $(BUILDDIR)/%, $(_TEST_OBJ)) $(OBJ)

_TEST = main_test.c hashmap_test.c
TEST = $(patsubst %, $(TESTDIR)/%, $(_TEST))

_TEST_DEPS = hashmap_test.h
TEST_DEPS = $(patsubst %, $(TESTDIR)/%, $(_TEST_DEPS)) $(DEPS)

# rules for src
$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# rules for test
$(BUILDDIR)/%.o: $(TESTDIR)/%.c $(TEST_DEPS)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(BUILDDIR)/main $(BUILDDIR)/test

# compile src
$(BUILDDIR)/main: $(MAIN) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# compile test
$(BUILDDIR)/test: $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# run src
run: $(BUILDDIR)/main
	./$(BUILDDIR)/main

# run test
test: $(BUILDDIR)/test
	./$(BUILDDIR)/test

# valgrind for src
valgrind: $(BUILDDIR)/main
	$(VALGRIND) $(VALGRIND_FLAGS) $(VALGRIND_OUTPUT) ./$(BUILDDIR)/main

# valgrdind for test
valgrind_test: $(BUILDDIR)/test
	$(VALGRIND) $(VALGRIND_FLAGS) $(VALGRIND_OUTPUT_TEST) ./$(BUILDDIR)/test

# gdb for src
gdb: $(BUILDDIR)/main
	$(GDB) ./$(BUILDDIR)/main

# gdb for test
gdb_test: $(BUILDDIR)/test
	$(GDB) ./$(BUILDDIR)/test

# clean
.PHONY: clean
clean: 
	rm -rf $(BUILDDIR)
	rm -i $(LOGDIR)