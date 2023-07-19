#include "print.h"

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int
main()
{
    void *handle = dlopen("./libprint.so", RTLD_LAZY);
    if (handle == NULL) {
        printf("%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    void (*print_array)(int32_t *, size_t);
    print_array = (void (*)(int32_t *, size_t))dlsym(handle, "print_array");
    if (print_array == NULL) {
        printf("%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    int32_t array[] = { 30, 3, 2023 };
    print_array(array, 3);

    int ret = dlclose(handle);
    if (ret != 0) {
        printf("%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    return 0;
}
