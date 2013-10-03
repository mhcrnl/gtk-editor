CC=gcc
CFLAGS=-std=c99 -Wall -Wextra `pkg-config --cflags gtk+-2.0`
LDFLAGS=`pkg-config --libs gtk+-2.0`

editor: editor.c
	$(CC) $(CFLAGS) $(LDFLAGS) editor.c -o editor

clean:
	rm -f editor