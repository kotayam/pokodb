CC = gcc
CFLAGS = -Wall -Wextra -O2

BUILDDIR = build
SRCDIR = src
INCLUDEDIR = include

_OBJ = main.o hashmap.o
OBJ = $(patsubst %, $(BUILDDIR)/%, $(_OBJ))

_SRC = main.c hashmap.c
SRC = $(patsubst %, $(SRCDIR)/%, $(_SRC))

_DEPS = hashmap.h
DEPS = $(patsubst %, $(INCLUDEDIR)/%, $(_DEPS))


$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(INCLUDEDIR)/%.h
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(BUILDDIR)/main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean: 
	rm -rf $(BUILDDIR) main