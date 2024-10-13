
all: src/main.c src/init.c src/input.c src/draw.c
	@clang \
  -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX13.3.sdk \
  -Wl,-search_paths_first -Wl,-headerpad_max_install_names \
  -I /usr/local/include \
  src/draw.c \
  src/init.c \
  src/input.c \
  src/main.c \
  -o shooter \
  -L/usr/local/lib \
  -lSDL2 -lSDL2_mixer -lSDL2 -lSDL2_image -lSDL2 -lSDL2_ttf -lSDL2 -lm

