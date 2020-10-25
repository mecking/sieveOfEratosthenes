#!/bin/bash
#testes seriais
for i in {1..10}; do ./sieve_serial 1000000000; done
for i in {1..10}; do ./sieve_serial 2000000000; done

#testes paralelos
export OMP_SCHEDULE=dynamic
for i in {1..10}; do ./sieve_parallel 1000000000 2; done
for i in {1..10}; do ./sieve_parallel 1000000000 4; done
for i in {1..10}; do ./sieve_parallel 1000000000 8; done
for i in {1..10}; do ./sieve_parallel 2000000000 2; done
for i in {1..10}; do ./sieve_parallel 2000000000 4; done
for i in {1..10}; do ./sieve_parallel 2000000000 8; done
export OMP_SCHEDULE=guided
for i in {1..10}; do ./sieve_parallel 1000000000 2; done
for i in {1..10}; do ./sieve_parallel 1000000000 4; done
for i in {1..10}; do ./sieve_parallel 1000000000 8; done
for i in {1..10}; do ./sieve_parallel 2000000000 2; done
for i in {1..10}; do ./sieve_parallel 2000000000 4; done
for i in {1..10}; do ./sieve_parallel 2000000000 8; done
export OMP_SCHEDULE=static
for i in {1..10}; do ./sieve_parallel 1000000000 2; done
for i in {1..10}; do ./sieve_parallel 1000000000 4; done
for i in {1..10}; do ./sieve_parallel 1000000000 8; done
for i in {1..10}; do ./sieve_parallel 2000000000 2; done
for i in {1..10}; do ./sieve_parallel 2000000000 4; done
for i in {1..10}; do ./sieve_parallel 2000000000 8; done
