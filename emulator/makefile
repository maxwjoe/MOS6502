# MAKEFILE TO BUILD 6502 EMULATOR LIBRARY

# === COMPILATION OPTIONS ===

CC = gcc
CFLAGS_DEBUG= -Wall -Werror -g -fsanitize=address,leak,undefined
CFLAGS= -fPIC

# === PATH AND OUTPUT OPTIONS ===

SRC_DIR=src
INCL_DIR=include
OBJ_DIR=obj
LIB_DIR=lib
BIN_DIR=bin

STATIC_LIB_NAME=MOS6502Static
DYNAMI_LIB_NAME=MOS6502

# === FILE PATTERNS ===

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# === BUILD RULES ===

all : $(LIB_DIR)/$(STATIC_LIB_NAME).a 

# Build Objects 
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCL_DIR) -c $< -o $@

# Build Static Library (Linux)
$(LIB_DIR)/$(STATIC_LIB_NAME).a : $(OBJ_FILES)
	mkdir -p $(LIB_DIR)
	ar rcs $(LIB_DIR)/$(STATIC_LIB_NAME).a $(OBJ_FILES)

clean :
	rm -r $(OBJ_DIR) $(LIB_DIR)