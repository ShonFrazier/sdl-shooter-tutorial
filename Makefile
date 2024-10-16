SOURCES = \
	src/init.c \
	src/draw.c \
	src/input.c \
	src/main.c \
	src/structs.c \
	src/stage.c

HEADERS = \
	src/main.h \
	src/input.h \
	src/defs.h \
	src/common.h \
	src/structs.h \
	src/init.h \
	src/draw.h \
	src/stage.h

MACOS_ISYSROOT = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk

INCLUDE_SEARCH = -I /usr/local/include -I /opt/local/include
LIBRARY_SEARCH = -L /usr/local/lib -L /opt/local/lib
LIBRARIES = -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm

# Ability to 'extend' structs. Use Apple's 'blocks'
C_FLAGS = -fms-extensions -fblocks
DEBUG = -g


all: shooter

clean:
	rm ./shooter

run: all
	./shooter

shooter: $(SOURCES) $(HEADERS)
	@clang \
	-isysroot $(MACOS_ISYSROOT) \
	-Wl,-search_paths_first -Wl,-headerpad_max_install_names \
	$(C_FLAGS) \
	$(DEBUG) \
	$(INCLUDE_SEARCH) \
	$(LIBRARY_SEARCH) \
	$(LIBRARIES) \
	$(SOURCES) \
	-o shooter

