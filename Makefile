SOURCES = \
	./src/dictionary.c \
	./src/custom_events.c \
	./src/corgipaths.c \
	./src/util/Object.c \
	./src/util/SparseArray.c \
	./src/init.c \
	./src/draw.c \
	./src/input.c \
	./src/main.c

HEADERS = \
	src/main.h \
	./src/input.h \
	./src/defs.h \
	./src/util/Object.h \
	./src/util/SparseArray.h \
	./src/corgipaths.h \
	./src/common.h \
	./src/dictionary.h \
	./src/custom_events.h \
	./src/structs.h \
	./src/init.h \
	./src/draw.h

C_STD = c11
FLAGS = -fms-extensions -fblocks -std=$(C_STD)

all: shooter

clean:
	rm -f ./shooter

run: shooter
	./shooter

shooter: $(SOURCES) $(HEADERS)
	@clang \
	$(FLAGS) \
	-isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX13.3.sdk \
	-Wl,-search_paths_first -Wl,-headerpad_max_install_names \
	-I /usr/local/include \
	-g \
	$(SOURCES) \
	-o shooter \
	-L/usr/local/lib \
	-lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm

