CC = gcc
CFLAGS = -Wall -Wextra -O2

ODIR = build
SDIR = src

_OBJ = main.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

_SRC = main.c
SRC = $(patsubst %, $(SDIR)/%, $(_SRC))

$(ODIR)/main: $(OBJ)
	$(CC) -o $@ $^

$(ODIR)/%.o: $(SDIR)/%.c
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean: 
	rm -rf $(ODIR) main