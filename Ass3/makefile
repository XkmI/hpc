PROGRAM = newton #test newtonIter complexTest ass3
CC = gcc
CFLAGS = -O2 -Wall#-g
LIBS = -lpthread -lm -fcx-limited-range#-lgsl -lgslcblas

.PHONY: all
all: $(PROGRAM)

$(PROGRAM) : %: %.c;
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.ppm
	rm -f $(PROGRAM)
