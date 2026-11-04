#include <stdio.h>

int main(void)
{
    int a = 5;
    int b = 7;

    puts("=== tokenization ===");
    {
        int result = a++ + b;
        printf("a+++b is a ++ + b, result=%d, a is now %d\n", result, a);
    }
    {
        int result = b-- - a;
        printf("b---a is b -- - a, result=%d, b is now %d\n", result, b);
    }

    puts("\n=== undefined behavior (not executed) ===");
#if 0
    a = b++ + ++b;
#endif
    puts("a = b++ + ++b modifies b twice without sequencing; the result is undefined.");
    puts("No value is printed for it because there is no portable value.");

    puts("\n=== safe expressions and precedence ===");
    {
        int w = 1;
        int x = 5;
        int y = 3;
        int z = 2;

        printf("x + y * z      = %d\n", x + y * z);
        printf("(x + y) * z    = %d\n", (x + y) * z);
        printf("x << y - z     = %d\n", x << (y - z));
        printf("(x << y) - z   = %d\n", (x << y) - z);
        printf("x < y == z     = %d\n", (x < y) == z);
        printf("x & y == w     = %d\n", x & (y == w));
        printf("(x & y) == w   = %d\n", (x & y) == w);
        printf("x ^ y & z      = %d\n", x ^ (y & z));
        printf("(x ^ y) & z    = %d\n", (x ^ y) & z);
        printf("x && y || z    = %d\n", (x && y) || z);
        printf("x || y && z    = %d\n", x || (y && z));
        printf("(x || y) && z  = %d\n", (x || y) && z);
    }

    puts("\nParentheses change meaning:");
    printf("2 + 3 * 4      = %d\n", 2 + 3 * 4);
    printf("(2 + 3) * 4    = %d\n", (2 + 3) * 4);
    printf("1 << 2 + 1     = %d\n", 1 << (2 + 1));
    printf("(1 << 2) + 1   = %d\n", (1 << 2) + 1);

    return 0;
}
