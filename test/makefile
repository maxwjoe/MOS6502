# MAKEFILE TO BUILD UNIT TESTS

# === COMPILATION OPTIONS ===

CC = gcc
CFLAGS =

# === PATH AND OUTPUT OPTIONS ===

EAGLE_INCL_DIR=include
EAGLE_LIB_DIR=lib
EAGLE_LIB_NAME=libEagle

EMULA_INCL_DIR=../emulator/include
EMULA_LIB_DIR=../emulator/lib
EMULA_LIB_NAME=MOS6502Static

OBJ_DIR=obj
BIN_DIR=bin

# === BUILD RULES ===

all : $(BIN_DIR)/testBed

$(BIN_DIR)/testBed : testBed.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(EMULA_INCL_DIR) -I$(EAGLE_INCL_DIR) -o $@ $^ -L./ -l:$(EMULA_LIB_DIR)/$(EMULA_LIB_NAME).a -l:lib/$(EAGLE_LIB_NAME).so

clean :
	rm -r $(BIN_DIR)