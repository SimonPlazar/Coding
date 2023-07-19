#include <stdint.h>
#include <stdio.h>

struct struct_normal
{
    uint8_t  a;  // 1 B
    uint16_t b;  // 2 B
    uint32_t c;  // 4 B
    float    d;  // 4 B
    double   e;  // 8 B
};               // == 24 B (20 B v 32-bitnem načinu)

struct __attribute__ ((packed)) struct_packed
{
    uint8_t  a;  // 1 B
    uint16_t b;  // 2 B
    uint32_t c;  // 4 B
    float    d;  // 4 B
    double   e;  // 8 B
};               // == 19 B

int
main()
{
    struct struct_normal struct_normal;
    struct struct_packed struct_packed;

    printf("Velikost strukture 'normal': %ld B\n", sizeof(struct_normal));
    printf("Velikost strukture 'packed': %ld B\n", sizeof(struct_packed));

	printf("\n");
	printf("Naslovi strukture 'normal':\n");
    printf("Naslov a (uint8_t):  %p\n", (void *)&struct_normal.a);
    printf("Naslov b (uint16_t): %p\n", (void *)&struct_normal.b);
    printf("Naslov c (uint32_t): %p\n", (void *)&struct_normal.c);
    printf("Naslov d (float):    %p\n", (void *)&struct_normal.d);
    printf("Naslov e (double):   %p\n", (void *)&struct_normal.e);
    
	printf("\n");
	printf("Naslovi strukture 'packed':\n");
    printf("Naslov a (uint8_t):  %p\n", (void *)&struct_packed.a);
    printf("Naslov b (uint16_t): %p\n", (void *)&struct_packed.b);
    printf("Naslov c (uint32_t): %p\n", (void *)&struct_packed.c);
    printf("Naslov d (float):    %p\n", (void *)&struct_packed.d);
    printf("Naslov e (double):   %p\n", (void *)&struct_packed.e);

    return 0;
}
