CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall -lm -pg -O1
CFLAGS_PARALLEL = -DPARALLEL -fopenmp

# the build target executable:
TARGET = sieve_serial sieve_parallel

all: $(TARGET)

sieve_parallel: sieve.c
	$(CC) -o sieve_parallel sieve.c $(CFLAGS) $(CFLAGS_PARALLEL)

sieve_serial: sieve.c
	$(CC) -o sieve_serial sieve.c $(CFLAGS)

clean:
	rm -rf sieve_serial sieve_parallel
