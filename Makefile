CFLAGS = -O3 -std=c11 -Wall -Werror -Wpedantic -Wextra -g -D _DEFAULT_SOURCE -DNCURSES_STATIC
BIN = terminal-bird
PREFIX = /usr/local
INSTALLPATH = ${DESTDIR}${PREFIX}/games
LIBS = -lncursesw -lsqlite3 -lcjson
DEPS = src/configuration.h src/headers.h src/leaderboard_db.h
OBJ = src/main.o src/pipe_nodes.o src/visuals.o src/menu.o src/leaderboard_db.o src/configuration.o
HOME_DIR := $(shell echo ~$(SUDO_USER))

%.o: %.c $(DEPS)

		@echo "*** Creating object ***"
		$(CC) -c -o $@ $< $(CFLAGS)

${BIN}: $(OBJ)

		@echo
		@echo "*** Creating directory $(HOME_DIR)/.Terminal-Bird ***"
		mkdir -p $(HOME_DIR)/.Terminal-Bird
		cp configurations.json $(HOME_DIR)/.Terminal-Bird
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

		@echo "*** uninstalling directory $(HOME_DIR)/.Terminal-Bird ***"
		rm -rf $(HOME_DIR)/.Terminal-Bird
		@echo "*** uninstalling binary file ${INSTALLPATH}/${BIN} ***"
		rm -f ${INSTALLPATH}/${BIN}
		@echo "*** uninstalled ${BIN} successfully***"

.PHONY: clean

clean:

		@echo "*** Cleaning up $(BIN) and $(OBJ) ***"
		rm -f ${BIN} src/*.o
		@echo "*** Cleaned ***"
