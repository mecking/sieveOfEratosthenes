//inspired at https://www.codesdope.com / blog / article / prime - numbers - using - sieve - algorithm - in - c

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>

#ifdef PARALLEL
#include <omp.h>
#endif

#define SIZE 2000000000

int main(int argc, char *argv[]) {
	int i, j;
	long int number, square;
	static int64_t primes[SIZE + 1];
	uint64_t	sum = 0;
	clock_t t;

#ifdef PARALLEL	
	int num_threads;
	if (argc != 2 ) {
		printf("Usage: ./sieve number_of_threads\n");
		exit (1);
	}
	num_threads = atoi(argv[1]);
#endif	
	number = SIZE;
	printf("Size: %lu\n", number);
	square = sqrt(number);
	printf("Square: %lu\n", square);
        
	t = clock();
	//parallel section
#ifdef PARALLEL	
	#pragma omp parallel num_threads(num_threads) shared(primes, sum) private(i, j)
	{
	#pragma omp single 
	printf("Number of threads: %d\n", omp_get_num_threads());
	#pragma omp for
#endif	
	for (i = 2; i <= number; i++) 
		primes[i] = i;
        
#ifdef PARALLEL	
	#pragma omp for schedule(dynamic)
#endif	
	for (i = 2; i <= square; i++) {
		if (primes[i] != 0) {
			for (j = 2; j < number; j++) {
				if (primes[i] * j > number)
					break;
				else
					primes[primes[i] * j] = 0;
			}
		}
	}
#ifdef PARALLEL	
        #pragma omp for reduction(+:sum)
#endif	
	for (i = 2; i <= number; i++) {
		if (primes[i])
			sum++;
	}
#ifdef PARALLEL	
	}
#endif	
	/* if (print) {
		for (i = 2; i <= number; i++) {
			if (primes[i] != 0)
				printf("%" PRId64 "\n", primes[i]);
		}
	} */
	t = clock() - t;
	printf("Found %" PRIu64 " prime number(s), timespent: %f\n", sum, ((double)t)/CLOCKS_PER_SEC);
	return 0;
}
