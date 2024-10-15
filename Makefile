SOURCES = \
  src/init.c \
  src/draw.c \
  src/input.c \
  src/main.c

HEADERS = \
  src/main.h \
  src/input.h \
  src/defs.h \
  src/common.h \
  src/structs.h \
  src/init.h \
  src/draw.h

INCLUDE_SEARCH = -I /usr/local/include
LIBRARY_SEARCH = -L /usr/local/lib
LIBRARIES = -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm

# Ability to 'extend' structs. Use Apple's 'blocks'
C_FLAGS = -fms-extensions -fblocks
DEBUG = -g
	
all: shooter

shooter: $(SOURCES) $(HEADERS)
	@clang \
	-isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX13.3.sdk \
	-Wl,-search_paths_first -Wl,-headerpad_max_install_names \
	$(C_FLAGS) \
	$(DEBUG) \
	$(INCLUDE_SEARCH) \
	$(SOURCES) \
	$(LIBRARY_SEARCH) \
	$(LIBRARIES) \
	-o shooter
