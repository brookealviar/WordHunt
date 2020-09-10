CC = -gcc
CFLAGS = -g3 -std=c99 -pedantic -Wall

Boggle:  Boggle.c
	${CC} ${CFLAGS} -o Boggle Boggle.c

clean:
	rm -f Boggle *.o
