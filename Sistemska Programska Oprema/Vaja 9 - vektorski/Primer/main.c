#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdalign.h>
#include <math.h>

// Knjižnica
#include <immintrin.h>

int main()
{
    printf("START A\n");

    // Število elementov v poljih
    // Od kod ta vrednost
    int n = 134217728;

    // Merjenje časa
    clock_t start = clock(), difference;

    float *array_1 = (float*)aligned_alloc(32, n * sizeof(float));
    float *array_2 = (float*)aligned_alloc(32, n * sizeof(float));
    float *result = (float*)aligned_alloc(32, n * sizeof(float));
    
    // Nastavimo začetne vrednosti polj
    for (int i = 0; i < n; i++)
    {
        array_1[i] = 10;
        array_2[i] = 20;
    }

    // Čas potreben za inicializacijo polj
    difference = clock() - start;
    printf("Time init: %ld ms\n", difference * 1000 / CLOCKS_PER_SEC);

    //
    // Iterativni izračun
    //
    start = clock();

    for (int i = 0; i < n; i++)
    {
        result[i] = array_1[i] + array_2[i];
    }

    // Čas potreben za izračun
    difference = clock() - start;
    printf("Result 0: %f\n", result[0]);
    printf("Time iter calc: %ld ms\n", difference * 1000 / CLOCKS_PER_SEC);

    //
    // Vektorski izračun
    //
    start = clock();

    __m256 a_vect, b_vect, res_vect;

    for (int i = 0; i < n; i += 8)
    {
        a_vect = _mm256_load_ps(array_1 + i);
        b_vect = _mm256_load_ps(array_2 + i);
        res_vect = _mm256_add_ps(a_vect, b_vect);

        _mm256_store_ps(result + i, res_vect);
    }

    // Čas potreben za izračun
    difference = clock() - start;
    printf("Result 0: %f\n", result[0]);
    printf("Time vect calc: %ld ms\n", difference * 1000 / CLOCKS_PER_SEC);

    printf("END A\n");

    return 0;
}