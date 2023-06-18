CC     = gcc
CFLAGS = --std=gnu99 -Wall -g

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

OBJS    = $(OBJ_DIR)/parse.o

.PHONY = all default test clean

all: llc

help:
	@echo "Targets: help, all, llc, test, and clean"

llc: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/main.c $^

$(OBJ_DIR)/parse.o: $(SRC_DIR)/parse.c $(INC_DIR)/parse.h
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

test:
	@echo "Testing with test_file.txt ..."
	llc -f=test_file.txt

clean:
	$(RM) $(OBJ_DIR)/*.o llc
