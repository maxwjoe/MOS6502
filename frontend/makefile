# === COMPILATION OPTIONS ===

CC=gcc
CFLAGS=

# === PATH AND OUTPUT OPTIONS ===

SRC_DIR=src
INCL_DIR=include
OBJ_DIR=obj
BIN_DIR=bin
MAIN_SRC=frontend

EMULA_INCL_DIR=../emulator/include
EMULA_LIB_DIR=../emulator/lib
EMULA_LIB_NAME=MOS6502Static

# === FILE PATTERNS ===

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# === BUILD RULES ===

all : $(BIN_DIR)/frontend

# Build Objects
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCL_DIR) -c $< -o $@

# Build Frontend
$(BIN_DIR)/frontend : $(MAIN_SRC).c $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(EMULA_INCL_DIR) -o $@ $^ -L./ -l:$(EMULA_LIB_DIR)/$(EMULA_LIB_NAME).a -lncurses

clean :
	rm -r $(OBJ_DIR)
	rm -r $(BIN_DIR)

