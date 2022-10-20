PROGRAM = matFromFile diffusion
CC = gcc
CFLAGS = -O2 -Wall #-g
LIBS = -lOpenCL -lm #-lpthread -lgsl -lgslcblas

.PHONY: all
all: $(PROGRAM)

$(PROGRAM) : %: %.c;
	$(CC) -o $@ $< $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f *.o
	rm -f $(PROGRAM)
