PREFIX?=/usr/X11R6
CFLAGS?=-Os -pedantic -Wall

all:
	$(CC) $(CFLAGS) -I$(PREFIX)/include src/main.c -L$(PREFIX)/lib -lX11 -o wm

clean:
	rm -f wm

