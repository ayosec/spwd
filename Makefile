
all: spwd

spwd: spwd.c
	gcc -Wall -O2 -o spwd spwd.c

debug:
	gcc -Wall -g -O2 -o spwd.debug spwd.c
	gdb ./spwd.debug

clean:
	rm spwd

.PHONY: clean all debug
