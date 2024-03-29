CC = clang
CFLAGS = -ggdb3 -gdwarf-4 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wpedantic -Wextra -Wshadow -D _DEFAULT_SOURCE
LIBS = -lncursesw -lm
DEPS = src/headers.h src/objects.h
OBJ = src/flappybird.o src/visuals.o src/debug.o

%.o: %.c $(DEPS)
		@echo "*** Creating object ***"
		$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

flappybird: $(OBJ)
		@echo "*** Building the executable file ***"
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
		rm -f flappybird src/*.o