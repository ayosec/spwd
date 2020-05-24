DEST ?= /usr/local

SPWD_VERSION ?= $(shell git describe --tags)

BUILD = build
BIN = $(BUILD)/spwd

CFLAGS += -Wall -Wextra -Wpedantic -O2
OBJECTS := $(patsubst src/%.c,$(BUILD)/%.o,$(wildcard src/*.c))

.DEFAULT_GOAL = test

$(BUILD)/USAGE.h: src/USAGE.m4
	@mkdir -p $(dir $@)
	m4 -DSPWD_VERSION=$(SPWD_VERSION) $< | xxd -i > $@

$(BUILD)/%.o: src/%.c $(wildcard src/*.h) $(BUILD)/USAGE.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -g -o $@ $(OBJECTS)

all: $(BIN)

clean:
	rm -f $(BIN) $(OBJECTS) $(BUILD)/USAGE.h
	rmdir $(BUILD)

install: $(BIN)
	install -D -s -m 0755 -o root -g root $(BIN) $(DEST)/bin/spwd

test: all
	@./tests/run

.PHONY: all clean install test
