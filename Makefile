BIN = spwd
BINDBG = spwd.dbg
SOURCES = spwd.c

$(BIN): $(SOURCES)
	gcc -Wall -Wextra -Wpedantic -O2 -o $(BIN) $(SOURCES)

$(BINDBG): $(SOURCES)
	gcc -Wall -Wextra -Wpedantic -g -O2 -o $(BINDBG) $(SOURCES)

clean:
	rm -f $(BIN) $(BINDBG)

all: $(BIN)

debug: $(BINDBG)

install: all
	install -s -m 0755 -o root -g root spwd /usr/local/bin

.PHONY: all debug clean install test
