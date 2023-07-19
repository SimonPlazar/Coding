#ifndef MY_BUFFER_H
#define MY_BUFFER_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

uint16_t *buffer_alloc(size_t size);

void buffer_free(uint16_t *buffer);

void buffer_fill(uint16_t *buffer);

void buffer_print(uint16_t *buffer);

#endif // MY_BUFFER_H
