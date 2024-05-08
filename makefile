CC = clang
CFLAGS = -O3 -std=c11 -Wall -Werror -Wpedantic -Wextra -Wshadow -D _DEFAULT_SOURCE
LIBS = -lncursesw
DEPS = src/headers.h
OBJ = src/main.o src/pipe_nodes.o src/visuals.o

%.o: %.c $(DEPS)
		@echo "*** Creating object ***"
		$(CC) -c -o $@ $< $(CFLAGS)

flappybird: $(OBJ)
		@echo "*** Building the executable file ***"
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
		rm -f flappybird src/*.o