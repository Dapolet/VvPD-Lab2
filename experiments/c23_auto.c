#include <stdio.h>

int main(void)
{
    auto value = 304;
    auto ratio = 1.5;

    printf("value = %d, sizeof(value) = %zu\n", value, sizeof(value));
    printf("ratio = %.2f, sizeof(ratio) = %zu\n", ratio, sizeof(ratio));
    return 0;
}
