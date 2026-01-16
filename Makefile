# ==========================================
#      MAKEFILE CLANG (Linux / Win)
# ==========================================

CC      = clang
CFLAGS  = -Iinclude -isystem lib -Wall -Wextra -O3 -g

# Détection de l'OS
ifeq ($(OS),Windows_NT)
    # --- WINDOWS ---
    detected_OS := Windows
    EXT = .exe
    RM = del /Q /S
    LIBS = -lglfw3 -lopengl32 -lgdi32 -lm
    FIX_PATH = $(subst /,\,$1)
else
    # --- LINUX / MAC ---
    detected_OS := Linux
    EXT = 
    RM = rm -rf
    LIBS = -lglfw -lGL -lm
endif

# Dossiers
SRC_DIR = src
OBJ_DIR = bin/obj
BIN_DIR = bin

# Nom de l'exécutable
TARGET = $(BIN_DIR)/Raymarching$(EXT)

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ==========================================
#            RÈGLES
# ==========================================

all: info $(TARGET)

info:
	@echo "Système : $(detected_OS)"
	@echo "Compilateur : $(CC)"

# Création de l'exécutable
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(OBJS) -o $@ $(LIBS)
	@echo ">>> SUCCÈS : $(TARGET) créé."

# Compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean info