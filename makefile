PROGRAM = test
CC = gcc
CFLAGS = -O0 -Wall
#LIBS = -lm -lgsl -lgslcblas

PROGRAM = test newtonIter complexTest

.PHONY: all
all: $(PROGRAM)

$(PROGRAM) : %: %.c;
	$(CC) -o $@ $< $(CFLAGS) 
#$(LIBS)

.PHONY: clean
clean:
	rm -f *.o
	rm -f $(PROGRAM)
	touch *.c
