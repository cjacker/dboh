DESTDIR=
PREFIX=/usr/local
CC=gcc

all:
	$(CC) -static -o c c.c ascii.c

install:
	install -m0755 c $(DESTDIR)/$(PREFIX)/bin

clean:
	rm -f c 
