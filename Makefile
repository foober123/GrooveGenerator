CC = clang
SRC = src/main.c src/grooveInfo.c src/grooveView.c src/grooveMetronome.c
OUT = main

INCLUDE_DIR = -Iinclude
CFLAGS = -Wall $(INCLUDE_DIR) 
LDFLAGS = -lm

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    # Linux setup
    CFLAGS += -I/usr/include/raylib
    LDFLAGS += -lraylib
else
    # Assume Windows
    CFLAGS += -Iraylib/include
    LDFLAGS += -Lraylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -fuse-ld=lld
    OUT := main.exe
endif

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
ifeq ($(UNAME_S), Linux)
	rm -f $(OUT)
else
	del /Q $(OUT)
endif
