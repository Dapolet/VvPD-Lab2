#include <stdio.h>

_Static_assert(sizeof(int) >= 2, "int is too small for this program");

int main(void)
{
    puts("_Static_assert passed at compile time");
    return 0;
}
