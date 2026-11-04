#include <stdio.h>

int main(void)
{
    // C99 line comment
    int sum = 0;

    /* Declaration inside the for init clause is also C99. */
    for (int i = 1; i <= 4; ++i) {
        sum += i;
    }

    printf("sum = %d\n", sum);
    return 0;
}
