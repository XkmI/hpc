PROGRAM = test newtonIter complexTest
CC = gcc
CFLAGS = -O0 -Wall
LIBS = -lpthread #-lm -lgsl -lgslcblas

.PHONY: all
all: $(PROGRAM)

$(PROGRAM) : %: %.c;
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f *.o
	rm -f $(PROGRAM)
	touch *.c
