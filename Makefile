CC = clang
SRC = src/main.c src/grooveInfo.c src/grooveView.c src/grooveMetronome.c src/grooveKeybinds.c src/theme.c
OUT = main

INCLUDE_DIR = -Iinclude
CFLAGS = -Wall $(INCLUDE_DIR)
LDFLAGS = -lm

ifeq ($(OS),Windows_NT)
    IS_WINDOWS = 1
else
    IS_WINDOWS = 0
endif

ifeq ($(IS_WINDOWS), 1)
    OUT = main.exe
    RAYLIB_DIR = external/raylib
    CFLAGS += -I$(RAYLIB_DIR)/include
    LDFLAGS += -L$(RAYLIB_DIR)/lib -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
    CFLAGS += --target=x86_64-w64-windows-gnu
    LDFLAGS += --target=x86_64-w64-windows-gnu
else
    OUT = main
    CFLAGS += -I/usr/include/raylib
    LDFLAGS += -lraylib -lm
endif

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
ifeq ($(IS_WINDOWS), 1)
	del /Q $(OUT)
else
	rm -f $(OUT)
endif
