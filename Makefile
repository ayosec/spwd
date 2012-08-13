
all: spwd

spwd: spwd.c
	gcc -Wall -O2 -o spwd spwd.c

clean:
	rm spwd

.PHONY: clean all
