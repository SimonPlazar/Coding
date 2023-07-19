#include <stdint.h>
#include <stdio.h>

static uint8_t
check_bit(uint8_t value, uint8_t i)
{
    uint8_t bit = (value >> i) & 1;

    return bit;
}

static uint8_t
set_bit(uint8_t value, uint8_t i)
{
    value = value | (1 << i);

    return value;
}

static uint8_t
clear_bit(uint8_t value, uint8_t i)
{
    value = value & ~(1 << i);

    return value;
}

static uint8_t
set_bits(uint8_t value, uint8_t mask)
{
    value = value | mask;

    return value;
}

static uint8_t
clear_bits(uint8_t value, uint8_t mask)
{
    value = value & ~mask;

    return value;
}

static void
print_bits(uint8_t value)
{
    for (int8_t i = 7; i >= 0; i--) {
        printf("%u", check_bit(value, i));
        if (i % 4 == 0) {
            printf(" ");
        }
    }
    printf("(%u)\n", value);
}

int
main()
{
    uint8_t value;

    // Test funkcije print_bits
    printf("\nTest funkcije print_bits:\n");
    
    value = 1;
    print_bits(value);

    value = 15;
    print_bits(value);

    value = 128;
    print_bits(value);

    // Preveri bit
    printf("\nPreveri bit:\n");
    
    value = 150;
    print_bits(value);
    printf("bit %u : %u\n", 0, check_bit(value, 0));
    printf("bit %u : %u\n", 1, check_bit(value, 1));
    printf("bit %u : %u\n", 4, check_bit(value, 4));
    printf("bit %u : %u\n", 5, check_bit(value, 5));

    // Postavi bit
    printf("\nPostavi bit:\n");
    
    value = 0;
    value = set_bit(value, 0);
    print_bits(value);

    value = 0;
    value = set_bit(value, 0);
    value = set_bit(value, 1);
    value = set_bit(value, 2);
    value = set_bit(value, 3);
    print_bits(value);

    value = 0;
    value = set_bit(value, 7);
    print_bits(value);

    // Izbrisi bit
    printf("\nIzbrisi bit:\n");
    
    value = 255;
    value = clear_bit(value, 0);
    print_bits(value);

    value = 255;
    value = clear_bit(value, 0);
    value = clear_bit(value, 1);
    value = clear_bit(value, 2);
    value = clear_bit(value, 3);
    print_bits(value);

    value = 255;
    value = clear_bit(value, 7);
    print_bits(value);

    // Postavi bite z masko
    printf("\nPostavi bite z masko:\n");
    
    value = 0;
    value = set_bits(value, 0x01);
    print_bits(value);

    value = 0;
    value = set_bits(value, 0x0f);
    print_bits(value);

    value = 0;
    value = set_bits(value, 0x80);
    print_bits(value);

    // Izbrisi bite z masko
    printf("\nIzbrisi bite z masko:\n");

    value = 255;
    value = clear_bits(value, 0x01);
    print_bits(value);

    value = 255;
    value = clear_bits(value, 0x0f);
    print_bits(value);

    value = 255;
    value = clear_bits(value, 0x80);
    print_bits(value);
}
