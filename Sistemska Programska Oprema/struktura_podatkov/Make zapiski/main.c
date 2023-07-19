#include "my_func.h"

int
main()
{
    struct my_struct ms = {
        .int_data = 2023,
        .float_data = 3.14,
        .str_data = "sistemska programska oprema"
    };

    my_func(&ms);

    return 0;
}
