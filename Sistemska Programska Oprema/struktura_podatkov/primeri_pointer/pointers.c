#include <stdint.h>
#include <stdio.h>

struct data
{
    float data_float;
    uint16_t data_uint;
};

union interface
{
    uint8_t buffer[6]; // float (4 B) + uint16_t (2 B) == 6 B
    struct data data;
};

int main()
{
    float data_float = 522.255;
    uint16_t data_uint = 255; // Preveri vrednosti 256 in 257
    
    printf("\n");
    printf("Buffer\n");
    printf("------\n");
    
    uint8_t data_buffer[6] = { 1, 2, 3, 4, 5, 6 };

    float *data_buffer_float = (float *)&data_buffer[0];
    *data_buffer_float = data_float;

    uint16_t *data_buffer_uint = (uint16_t *)&data_buffer[4];
    *data_buffer_uint = data_uint;

    // Krajša alternativa
    // *(float *)&data_buffer[0] = data_float;
    // *(uint16_t *)&data_buffer[4] = data_uint;

    printf("Izpis surovih vrednosti v pomnilniku:\n");
    printf("  Lokacija 0: %d\n", data_buffer[0]);
    printf("  Lokacija 1: %d\n", data_buffer[1]);
    printf("  Lokacija 2: %d\n", data_buffer[2]);
    printf("  Lokacija 3: %d\n", data_buffer[3]);
    printf("  Lokacija 4: %d\n", data_buffer[4]);
    printf("  Lokacija 5: %d\n", data_buffer[5]);

    printf("Izpis shranjenih vrednosti:\n");
    printf("  Vrednost float: %f\n", *(float *)&data_buffer[0]);
    printf("  Vrednost uint:  %d\n", *(uint16_t *)&data_buffer[4]);

    printf("\n");
    printf("Structure\n");
    printf("---------\n");
    
    struct data data;
    data.data_float = data_float;
    data.data_uint = data_uint;

    uint8_t *data_ptr = (uint8_t *)&data;

    printf("Izpis surovih vrednosti v pomnilniku:\n");
    printf("  Lokacija 0: %d\n", data_ptr[0]);
    printf("  Lokacija 1: %d\n", data_ptr[1]);
    printf("  Lokacija 2: %d\n", data_ptr[2]);
    printf("  Lokacija 3: %d\n", data_ptr[3]);
    printf("  Lokacija 4: %d\n", data_ptr[4]);
    printf("  Lokacija 5: %d\n", data_ptr[5]);

    printf("Izpis shranjenih vrednosti:\n");
    printf("  Vrednost float: %f\n", *(float *)&data_ptr[0]);
    printf("  Vrednost uint:  %d\n", *(uint16_t *)&data_ptr[4]);

    printf("\n");
    printf("Union\n");
    printf("-----\n");

    union interface interface;

    interface.data.data_float = data_float;
    interface.data.data_uint = data_uint;

    printf("Izpis surovih vrednosti v pomnilniku:\n");
    printf("  Lokacija 0: %d\n", interface.buffer[0]);
    printf("  Lokacija 1: %d\n", interface.buffer[1]);
    printf("  Lokacija 2: %d\n", interface.buffer[2]);
    printf("  Lokacija 3: %d\n", interface.buffer[3]);
    printf("  Lokacija 4: %d\n", interface.buffer[4]);
    printf("  Lokacija 5: %d\n", interface.buffer[5]);

    printf("Izpis shranjenih vrednosti:\n");
    printf("  Vrednost float: %f\n", *(float *)&interface.buffer[0]);
    printf("  Vrednost uint:  %d\n", *(uint16_t *)&interface.buffer[4]);

    return 0;
}
