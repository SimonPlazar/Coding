#include <stdio.h>

double
powern(double x, size_t n)
{
    double y = 1.0;
    for (size_t i = 1; i <= n; i++) {
	    y *= x;
    }
	
    return y;
}
	
int
main()
{
    double sum = 0.0;
    
    for (size_t i = 1; i <= 100000000; i++) {
        sum += powern(i, i % 5);
    }

	printf("sum = %.0f\n", sum);
	
    return 0;
}
