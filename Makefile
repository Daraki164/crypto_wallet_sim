CC = gcc
CFLAGS = -Wall -Wextra -O2
DEBUG_FLAGS = -Wall -Wextra -g -O0

INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
HIS_DIR = history

MKDIR_CMD = mkdir -p
RM_CMD = rm -rf

OBJS = \
	$(OBJ_DIR)/wallet.o \
	$(OBJ_DIR)/main.o \
	$(OBJ_DIR)/log.o \
	$(OBJ_DIR)/transaction.o \
	$(OBJ_DIR)/history.o \


all: clean diretorio $(BIN_DIR)/main


debug: CFLAGS = $(DEBUG_FLAGS)
debug: all

$(BIN_DIR)/main: diretorio $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

diretorio:
	$(MKDIR_CMD) $(BIN_DIR) $(OBJ_DIR) $(HIS_DIR)

clean: 
	$(RM_CMD) $(BIN_DIR) $(OBJ_DIR)

.PHONY: all debug diretorio clean