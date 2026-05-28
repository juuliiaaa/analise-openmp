#include <stdio.h>
#include <time.h>

long long fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

int main() {
    int n = 45;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    long long result = fib(n);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("fib(%d) = %lld\n", n, result);
    printf("Tempo sequencial: %.4f s\n", elapsed);

    return 0;
}