PROGRAM = newton #test newtonIter complexTest ass3
CC = gcc
CFLAGS = -O2 -Wall -fcx-limited-range#-g
LIBS = -lpthread -lm#-lgsl -lgslcblas

.PHONY: all
all: $(PROGRAM)

$(PROGRAM) : %: %.c;
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.ppm
	rm -f $(PROGRAM)
