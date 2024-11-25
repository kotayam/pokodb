CC = gcc
CFLAGS = -Wall -Wextra -O2

VALGRIND = valgrind
LOGDIR = log
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --verbose --log-file=$(LOGDIR)/log

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

valgrind:
	$(VALGRIND) $(VALGRIND_FLAGS) make run

.PHONY: clean

clean: 
	rm -rf $(BUILDDIR) main