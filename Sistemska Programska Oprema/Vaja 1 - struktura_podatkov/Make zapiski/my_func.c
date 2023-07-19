#include "my_func.h"

#include <stdio.h>

void my_func(const struct my_struct * const ms)
{
    printf("Int data:    %d\n", ms->int_data);
    printf("Float data:  %f\n", ms->float_data);
    printf("String data: %s\n", ms->str_data);
}
