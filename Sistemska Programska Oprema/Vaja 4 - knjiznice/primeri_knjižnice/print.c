#include "print.h"

#include <stdio.h>

void
print_array(int32_t *a, size_t n)
{
    printf("[");
    for (size_t i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("]\n");
}
