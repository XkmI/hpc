CC = gcc
CFLAGS = -O0 -Wall
#LIBS = -lm -lgsl -lgslcblas

PROGRAM = test

all: $(PROGRAM)

$(PROGRAM) : %: %.c;
	$(CC) -o $@ $< $(CFLAGS) 
#$(LIBS)

clean:
	rm -f *.o
	touch *.c