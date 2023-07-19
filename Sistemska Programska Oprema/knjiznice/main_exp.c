#include "add.h"
#include "mul.h"

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    void *handle = dlopen("./libmath.so", RTLD_LAZY);
    if (handle == NULL) {
        printf("%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    int32_t (*add)(int32_t, int32_t);
    add = (int32_t (*)(int32_t, int32_t))dlsym(handle, "add");
    if (add == NULL) {
        printf("%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    printf("%d\n", add(2, 4));


    float (*mul)(float, float);
    mul = (float (*)(float, float))dlsym(handle, "mul");
    if (mul == NULL) {
        printf("%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    
    printf("%f\n", mul(2, 4));

    int ret = dlclose(handle);
    if (ret != 0) {
        printf("%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    return 0;
}