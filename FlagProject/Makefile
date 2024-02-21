CC= gcc

CFLAGS=-c -Wall

all: test

test: test.o flag.o fileoperator.o csvparser.o
	$(CC) test.o fileoperator.o csvparser.o flag.o -o test

test.o: test.c
	$(CC) $(CFLAGS) test.c

fileoperator.o: fileoperator.c
	$(CC) $(CFLAGS) fileoperator.c

csvparser.o: csvparser.c
	$(CC) $(CFLAGS) csvparser.c

flag.o: flag.c
	$(CC) $(CFLAGS) flag.c

clean: 
	rm -rf *.o test

