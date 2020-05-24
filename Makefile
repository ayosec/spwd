DEST ?= /usr/local

SPWD_VERSION ?= $(shell git describe --tags)

BUILD = build
BIN = $(BUILD)/spwd
MANPAGE= $(BUILD)/spwd.1

CFLAGS += -Wall -Wextra -Wpedantic -O2
OBJECTS := $(patsubst src/%.c,$(BUILD)/%.o,$(wildcard src/*.c))

M4_DOCS = m4 -DSPWD_VERSION=$(SPWD_VERSION)

.DEFAULT_GOAL = test

$(BUILD)/%.o: src/%.c $(wildcard src/*.h) $(BUILD)/USAGE.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD)/USAGE.h: doc/USAGE.m4
	@mkdir -p $(dir $@)
	$(M4_DOCS) $< | xxd -i > $@

$(MANPAGE): doc/spwd.1.scd
	@mkdir -p $(dir $@)
	$(M4_DOCS) $< | scdoc > $@

$(BIN): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -g -o $@ $(OBJECTS)

all: $(BIN)

clean:
	rm -f $(BIN) $(OBJECTS) $(BUILD)/USAGE.h $(MANPAGE)
	rmdir $(BUILD)

install: $(BIN) $(MANPAGE)
	install -D -s -m 0755 -o root -g root $(BIN) $(DEST)/bin/spwd
	install -D -m 0644 -o root -g root $(MANPAGE) $(DEST)/share/man/man1/spwd.1

test: all
	@./tests/run

.PHONY: all clean install test
