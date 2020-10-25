// inspired at https://www.codesdope.com / blog / article / prime - numbers - using - sieve - algorithm - in - c

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>
#include <omp.h>

int main(int argc, char *argv[]) {
	long		i         , j, size, square;
	int 		chunk = 0, num_threads = 0;
	uint64_t        *primes, sum = 0;
	double		start_time, time;
	omp_sched_t schedule;

	//serial section
	start_time = omp_get_wtime();
	size = atoi(argv[1]);

#ifdef PARALLEL
	if (argc != 3) {
		printf("Usage: ./sieve_sieve size\n");
		printf("Usage: ./sieve_parallel size number_of_threads\n");
		exit(1);
	}
	num_threads = atoi(argv[2]);
#endif

	square = sqrt(size);

	primes = malloc(1 + (size * sizeof(uint64_t)));
	if (!primes) {
		perror("malloc arr");
		exit(EXIT_FAILURE);
	};

	//parallel section
#ifdef PARALLEL
#pragma omp parallel num_threads(num_threads) shared(primes, sum) private(i, j)
	{
//#pragma omp single
//		printf("Number of threads: %d\n", omp_get_num_threads());
#pragma omp for
#endif
		for (i = 2; i <= size; i++)
			primes[i] = i;

#ifdef PARALLEL
#pragma omp for schedule(runtime)
#endif
		for (i = 2; i <= square; i++) {
			if (primes[i] != 0) {
				for (j = 2; j < size; j++) {
					if (primes[i] * j > size)
						break;
					else
						primes[primes[i] * j] = 0;
				}
			}
		}
		omp_get_schedule(&schedule, &chunk);
#ifdef PARALLEL
#pragma omp for reduction(+:sum)
#endif
		for (i = 2; i <= size; i++) {
			if (primes[i])
				sum++;
		}
#ifdef PARALLEL
	}
#endif
	free(primes);
	time = omp_get_wtime() - start_time;
	
	if (num_threads) {
		//printf("num_threads,size,time,schedule,chunk\n");
		printf("%d,%ld,%lf,%d,%d\n", num_threads,size,time,schedule,chunk);
	} else {
		//printf("num_threads,size,time,schedule,chunk\n");
		printf("%d,%ld,%lf,0,0\n", num_threads,size,time);
	}
	//printf("Size: %ld\n", size);
	//printf("Square: %ld\n", square);
	//printf("Timespent: %lf\n", time);
	//printf("Found prime number(s): %" PRIu64 "\n", sum); 
	return 0;
}
