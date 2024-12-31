CFLAGS = -O3 -std=c11 -Wall -Werror -Wpedantic -Wextra -g -D _DEFAULT_SOURCE -DNCURSES_STATIC
BIN = terminal-bird
PREFIX = /usr/local
INSTALLPATH = ${DESTDIR}${PREFIX}/games
LIBS = -lncursesw
DEPS = src/headers.h
OBJ = src/main.o src/pipe_nodes.o src/visuals.o

%.o: %.c $(DEPS)

		@echo "*** Creating object ***"
		$(CC) -c -o $@ $< $(CFLAGS)

${BIN}: $(OBJ)

		@echo 
		@echo "*** Building the executable file ***"
		$(CC) -o $@ $(OBJ) $(CFLAGS) $(LIBS)

install: ${BIN}

		@echo
		@echo "*** Installing binary file to ${INSTALLPATH}/${BIN} ***"
		mkdir -p ${INSTALLPATH}
		cp ${BIN} ${INSTALLPATH}
		chmod 0755 ${INSTALLPATH}/${BIN}
		@echo
		@echo "*** Installed ${BIN} successfully ***"

uninstall:

		@echo "*** uninstalling binary file ${INSTALLPATH}/${BIN} ***"
		rm -f ${INSTALLPATH}/${BIN}
		@echo "*** uninstalled ${BIN} successfully***"

.PHONY: clean

clean:

		@echo "*** Cleaning up $(BIN) and $(OBJ) ***"
		rm -f ${BIN} src/*.o
		@echo "*** Cleaned ***"
