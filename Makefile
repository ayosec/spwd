DEST ?= /usr/local

BUILD = build
BIN = $(BUILD)/spwd

CFLAGS = -Wall -Wextra -Wpedantic -O2
OBJECTS := $(patsubst src/%.c,$(BUILD)/%.o,$(wildcard src/*.c))

all: $(BIN)

build/USAGE.h: src/USAGE.txt
	@mkdir -p $(dir $@)
	xxd -i < $< > $@

build/%.o: src/%.c $(wildcard src/*.h) build/USAGE.h
	@mkdir -p $(dir $@)
	gcc $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJECTS)
	@mkdir -p $(dir $@)
	gcc $(CFLAGS) -g -o $@ $(OBJECTS)

clean:
	rm -f $(BIN) $(OBJECTS) build/USAGE.h
	rmdir $(BUILD) || echo "$(BUILD) is not empty"

install: $(BIN)
	install -s -m 0755 -o root -g root $(BIN) $(DEST)/bin/spwd

test: all
	@./tests/run

.PHONY: all clean install test
