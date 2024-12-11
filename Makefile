PROJ_NAME=Tetris

SRC_PATH = src
BUILD_PATH = build
BIN_PATH = $(BUILD_PATH)/bin

BIN_NAME = tetris

SOURCES = $(shell find $(SRC_PATH) -name '*.cpp' | sort -k 1nr | cut -f2-)
OBJECTS = $(SOURCES:$(SRC_PATH)/%.cpp=$(BUILD_PATH)/%.o)

CC=g++

CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -ansi      \
         -pedantic	\
		 -I include \
		 -std=c++11

# CC_SDL=`pkgconf --cflags --libs sdl2`
CC_SDL := `sdl2-config --libs --cflags` -lSDL2_ttf

all: $(BIN_PATH)/$(BIN_NAME)

$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "Linking: $@"
	$(CC) $(OBJECTS) -o $@ $(CC_SDL)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp
	@mkdir -p $(BUILD_PATH)
	@mkdir -p $(BIN_PATH)
	@echo "Making symlink: $(BIN_NAME) -> $<"
	rm -f $(BIN_NAME)
	ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)
	@echo "Compiling: $< -> $@"
	$(CC) $(CC_FLAGS) $(CC_SDL) -c $< -o $@
