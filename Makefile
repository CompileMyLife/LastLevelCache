CC = gcc
CFLAGS = --std=gnu99 -Wall -g

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
TST_DIR = tests
LOG_DIR = logs

OBJS = $(OBJ_DIR)/parse.o $(OBJ_DIR)/snoop.o $(OBJ_DIR)/cache.o $(OBJ_DIR)/PLRU.o \
	   $(OBJ_DIR)/ops.o
	   

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

$(OBJ_DIR)/ops.o: $(SRC_DIR)/ops.c $(INC_DIR)/ops.h
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)/PLRU.o: $(SRC_DIR)/PLRU.c $(INC_DIR)/PLRU.h
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

test0:
	@echo "Testing with tests/test0.txt ..."
	@echo "tests/test0.txt contains valid and invalid addresses to test parsing"
	./llc -f $(TST_DIR)/test0.txt > $(LOG_DIR)/llc_test0_log.txt

test1:
	@echo "Testing with tests/test1.txt ..."
	@echo "tests/test1.txt contain only read requests to same set"
	./llc -f $(TST_DIR)/test1.txt > $(LOG_DIR)/llc_test1_log.txt

test2:
	@echo "Testing with tests/test2.txt ..."
	@echo "tests/test2.txt contain read and write requests to same set"
	./llc -f $(TST_DIR)/test2.txt > $(LOG_DIR)/llc_test2_log.txt

clean:
	$(RM) $(OBJ_DIR)/*.o $(LOG_DIR)/*.txt ./llc
