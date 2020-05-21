BIN = spwd
SOURCES = spwd.c

$(BIN): $(SOURCES)
	gcc -Wall -Wextra -Wpedantic -O2 -o $(BIN) $(SOURCES)

clean:
	rm -f $(BIN)

all: $(BIN)

install: all
	install -s -m 0755 -o root -g root spwd /usr/local/bin

.PHONY: all clean install
