CC = gcc
CFLAGS = -Wall -Wextra -Og -ggdb3

VALGRIND = valgrind
LOGDIR = log
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --log-file=$(LOGDIR)/log

BUILDDIR = build
SRCDIR = src
INCLUDEDIR = include

_OBJ = main.o hashmap.o
OBJ = $(patsubst %, $(BUILDDIR)/%, $(_OBJ))

_SRC = main.c hashmap.c
SRC = $(patsubst %, $(SRCDIR)/%, $(_SRC))

_DEPS = hashmap.h errors.h
DEPS = $(patsubst %, $(INCLUDEDIR)/%, $(_DEPS))


$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(BUILDDIR)/main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

run: $(BUILDDIR)/main
	./$(BUILDDIR)/main

valgrind: $(BUILDDIR)/main
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(BUILDDIR)/main

.PHONY: clean

clean: 
	rm -rf $(BUILDDIR) main