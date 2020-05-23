BUILD = build
BIN = $(BUILD)/spwd
BINDBG = $(BUILD)/spwd.dbg

CFLAGS = -Wall -Wextra -Wpedantic -O2
OBJECTS := $(patsubst src/%.c,$(BUILD)/%.o,$(wildcard src/*.c))

all: $(BIN) $(BINDBG)

build/%.o: src/%.c $(wildcard src/*.h)
	@mkdir -p $(BUILD)
	gcc $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJECTS)
	gcc $(CFLAGS) -o $(BIN) $(OBJECTS)

$(BINDBG): $(OBJECTS)
	gcc $(CFLAGS) -g -o $(BINDBG) $(OBJECTS)

clean:
	rm -f $(BIN) $(BINDBG) $(OBJECTS)
	rmdir $(BUILD)

debug: $(BINDBG)

install: $(BIN)
	install -s -m 0755 -o root -g root $(BIN) /usr/local/bin

test: all
	./tests.sh

.PHONY: all debug clean install test
