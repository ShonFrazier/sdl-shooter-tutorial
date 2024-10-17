SOURCES = \
	src/init.c \
	src/draw.c \
	src/input.c \
	src/main.c \
	src/structs.c \
	src/stage.c \
	src/util/list.c

HEADERS = \
	src/main.h \
	src/input.h \
	src/defs.h \
	src/common.h \
	src/structs.h \
	src/init.h \
	src/draw.h \
	src/stage.h \
	src/util/list.h

TEST_SOURCES = \
	src/util/tests/CuTest.c \
	src/util/tests/list-test.c \
	src/util/tests/RunTests.c \
	src/util/list.c

TEST_HEADERS = \
	src/util/tests/CuTest.h \
	src/util/tests/list-test.h \
	src/util/list.h

APP_TARGET_NAME = shooter
TEST_TARGET_NAME = tester

MACOS_ISYSROOT = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk

INCLUDE_SEARCH = -I /usr/local/include -I /opt/local/include
LIBRARY_SEARCH = -L /usr/local/lib -L /opt/local/lib
LIBRARIES = -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm

# Ability to 'extend' structs. Use Apple's 'blocks'
C_FLAGS = -fms-extensions -fblocks
DEBUG = -g


all: $(APP_TARGET_NAME)

clean:
	@rm -rf ./$(APP_TARGET_NAME){,.dSYM} ./$(TEST_TARGET_NAME){,.dSYM}
	@echo Done.

run: $(APP_TARGET_NAME)
	./$(APP_TARGET_NAME)

$(APP_TARGET_NAME): $(SOURCES) $(HEADERS)
	@echo Building...
	@clang \
	-isysroot $(MACOS_ISYSROOT) \
	-Wl,-search_paths_first -Wl,-headerpad_max_install_names \
	$(C_FLAGS) \
	$(DEBUG) \
	$(INCLUDE_SEARCH) \
	$(LIBRARY_SEARCH) \
	$(LIBRARIES) \
	$(SOURCES) \
	-o $(APP_TARGET_NAME) && echo Done.

test: $(TEST_TARGET_NAME)
	./$(TEST_TARGET_NAME)

$(TEST_TARGET_NAME): $(TEST_SOURCES) $(TEST_HEADERS)
	@echo Building...
	@clang \
	-isysroot $(MACOS_ISYSROOT) \
	-Wl,-search_paths_first -Wl,-headerpad_max_install_names \
	$(C_FLAGS) \
	$(INCLUDE_SEARCH) \
	$(LIBRARY_SEARCH) \
	$(LIBRARIES) \
	$(TEST_SOURCES) \
	-o $(TEST_TARGET_NAME) && echo Done.

