#include "spo_simd.h"

void fill_random(double* arr, size_t n) {
    srand(time(NULL));
    for (size_t i = 0; i < n; ++i) {
        arr[i] = (double)rand() / RAND_MAX * 10;
    }
}

int main() {
    double* a = aligned_alloc(16, SIZE * sizeof(double));
    double* b = aligned_alloc(16, SIZE * sizeof(double));
    double* c = aligned_alloc(16, SIZE * sizeof(double));

    fill_random(a, SIZE);
    fill_random(b, SIZE);

    clock_t start = clock(), difference;
    for (int i = 0; i < SIZE; i++)
    {
        c[i] = a[i] * b[i];
    }
    difference = clock() - start;
    printf("First: %f \tLast: %f\n", c[0], c[SIZE - 1]);
    printf("Time iter mul: %ld ms\n", difference * 1000 / CLOCKS_PER_SEC);
    
    start = clock();
    for (size_t i = 0; i < SIZE; i += 2) {
        __m128d vecA = _mm_load_pd(a + i);
        __m128d vecB = _mm_load_pd(b + i);
        __m128d vecC = _mm_mul_pd(vecA, vecB);
        _mm_store_pd(c + i, vecC);
    }
    difference = clock() - start;
    printf("First: %f\tLast: %f\n", c[0], c[SIZE - 1]);
    printf("Time vec mul: %ld ms\n", difference * 1000 / CLOCKS_PER_SEC);

    double maxResult = -RAND_MAX;
    double minResult = RAND_MAX;
    start = clock();
    for (int i = 0; i < SIZE; i++) {
        if (c[i] > maxResult) {
            maxResult = c[i];
        }
        if (c[i] < minResult) {
            minResult = c[i];
        }
    }
    difference = clock() - start;
    printf("Max: %f\tMin: %f\n", maxResult, minResult);
    printf("Time iter max min: %ld ms\n", difference * 1000 / CLOCKS_PER_SEC);

    double* max = aligned_alloc(16, 2 * sizeof(double));
    double* min = aligned_alloc(16, 2 * sizeof(double));

    __m128d maxVal = _mm_set1_pd(-RAND_MAX);
    __m128d minVal = _mm_set1_pd(RAND_MAX);

    start = clock();
    for (size_t i = 0; i < SIZE; i += 2) {
        __m128d vecA = _mm_load_pd(a + i);
        maxVal = _mm_max_pd(maxVal, vecA);
        minVal = _mm_min_pd(minVal, vecA);
    }
    _mm_store_pd(max, maxVal);
    _mm_store_pd(min, minVal);

    for (int i = 0; i < 2; i++)
    {
        if (max[i] > maxResult) {
            maxResult = max[i];
        }
        if (min[i] < minResult) {
            minResult = min[i];
        }
    }
    difference = clock() - start;
    printf("Max: %f\tMin: %f\n", maxResult, minResult);
    printf("Time vec max min: %ld ms\n", difference * 1000 / CLOCKS_PER_SEC);

    free(a);
    free(b);
    free(c);

    return 0;
}
