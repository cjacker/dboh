DESTDIR=
PREFIX=/usr/local
CC=gcc

all:
	$(CC) -static -o dboh dboh.c ascii.c

install:
	install -m0755 dboh $(DESTDIR)/$(PREFIX)/bin

clean:
	rm -f dboh
