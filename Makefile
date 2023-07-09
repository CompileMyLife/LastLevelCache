CC = gcc
CFLAGS = --std=gnu99 -Wall -g

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

OBJS = $(OBJ_DIR)/parse.o $(OBJ_DIR)/snoop.o $(OBJ_DIR)/cache.o

.PHONY = all default test clean

all: llc

help:
	@echo "Targets: help, all, llc, test0, and clean"

llc: $(OBJS)
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ $(SRC_DIR)/main.c $^

$(OBJ_DIR)/parse.o: $(SRC_DIR)/parse.c $(INC_DIR)/parse.h
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)/snoop.o: $(SRC_DIR)/snoop.c $(INC_DIR)/snoop.h
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)/cache.o: $(SRC_DIR)/cache.c $(INC_DIR)/cache.h
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

test0:
	@echo "Testing with test0.txt ..."
	./llc -f test0.txt

clean:
	$(RM) $(OBJ_DIR)/*.o llc
