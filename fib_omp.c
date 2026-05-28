#include <stdio.h>
#include <time.h>
#include <omp.h>

#define CUTOFF 30

long long fib(int n) {
    if (n <= 1) return n;

    if (n < CUTOFF) {
        return fib(n - 1) + fib(n - 2);
    }

    long long x, y;

    #pragma omp task shared(x)
    x = fib(n - 1);

    #pragma omp task shared(y)
    y = fib(n - 2);

    #pragma omp taskwait

    return x + y;
}

int main() {
    int n = 45;
    long long result;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("fib(%d) = %lld\n", n, result);
    printf("Tempo paralelo: %.4f s\n", elapsed);
    printf("Threads usadas: %d\n", omp_get_max_threads());

    return 0;
}