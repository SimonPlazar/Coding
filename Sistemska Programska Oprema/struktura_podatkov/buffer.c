#include "buffer.h"

uint16_t *buffer_alloc(size_t size){
    return malloc(sizeof(uint16_t) * size);
}

void buffer_free(uint16_t *buffer)
{
    free(buffer);
}

void buffer_fill(uint16_t *buffer)
{
    //*(float *)&data_buffer[0] = 3.14;
    //*(char *)&data_buffer[4] = 'S';

    char *buffer_char1 = (char *)&buffer[0];
    *buffer_char1 = 'S';

    char *buffer_char2 = (char *)&buffer[1];
    *buffer_char2 = 'P';

    char *buffer_char3 = (char *)&buffer[2];
    *buffer_char3 = 'O';

    float *data_buffer_float = (float *)&buffer[3];
    *data_buffer_float = 3.141593;
    
    uint32_t *data_buffer_uint = (uint32_t *)&buffer[7];
    *data_buffer_uint = 25947;

    char *buffer_char4 = (char *)&buffer[11];
    *buffer_char4 = '!';
}

void buffer_print(uint16_t *buffer)
{
    printf("%c\n", *(char *)&buffer[0]);
    printf("%c\n", *(char *)&buffer[1]);
    printf("%c\n", *(char *)&buffer[2]);
    printf("%f\n", *(float *)&buffer[3]);
    printf("%d\n", *(uint32_t *)&buffer[7]);
    printf("%c\n", *(char *)&buffer[11]);
}