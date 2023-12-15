CC = gcc
CFLAGS = -DDEBUG=0 --std=gnu99 -Wall

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
TST_DIR = tests
LOG_DIR = logs

OBJS = $(OBJ_DIR)/parse.o $(OBJ_DIR)/snoop.o $(OBJ_DIR)/cache.o $(OBJ_DIR)/PLRU.o \
	   $(OBJ_DIR)/ops.o
	   

.PHONY = all default test0 test1 test2 cc1 clean

all: llc

help:
	@echo "Targets: help, all, llc, test, and clean"

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

# Test each test target
test: test0 test1 test2 cc1 snoop_inval snoop_read snoop_write snoop_rwim
	@echo "Running all tests from tests/"

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

cc1:
	@echo "Testing with tests/cc1.din ..."
	./llc -f $(TST_DIR)/cc1.din > $(LOG_DIR)/llc_cc1_log.txt

snoop_inval:
	@echo "Testing with tests/snoop_inval.txt ..."
	./llc -f $(TST_DIR)/snoop_inval.txt > $(LOG_DIR)/llc_snoop_inval_log.txt

snoop_read:
	@echo "Testing with tests/snoop_read.txt ..."
	./llc -f $(TST_DIR)/snoop_read.txt > $(LOG_DIR)/llc_snoop_read_log.txt

snoop_write:
	@echo "Testing with tests/snoop_write.txt ..."	
	./llc -f $(TST_DIR)/snoop_write.txt > $(LOG_DIR)/llc_snoop_write_log.txt

snoop_rwim:
	@echo "Testing with tests/snoop_rwim.txt ..."
	./llc -f $(TST_DIR)/snoop_rwim.txt > $(LOG_DIR)/llc_snoop_rwim_log.txt

clean:
	$(RM) $(OBJ_DIR)/*.o $(LOG_DIR)/* ./llc
