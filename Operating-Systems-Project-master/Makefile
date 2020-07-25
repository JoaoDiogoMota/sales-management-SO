CC = gcc
CFLAGS = -Wall -Wextra -g

ma:
	$(CC) ma.c $(CFLAGS) -o ma

cv:
	$(CC) cv.c $(CFLAGS) -o cv

sv:
	$(CC) sv.c $(CFLAGS) -o sv

ag:
	$(CC) ag.c $(CFLAGS) -o ag

compile: ma cv sv ag

uninstall: clean

clean:
	rm -f ma
	rm -f cv
	rm -f sv
	rm -f ag
	rm *.txt
