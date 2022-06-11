DESTDIR=
PREFIX=/usr/local
CC=gcc

all:
	$(CC) -o dboh dboh.c

install:
	install -m0755 dboh $(DESTDIR)/$(PREFIX)/bin

clean:
	rm -f dboh
