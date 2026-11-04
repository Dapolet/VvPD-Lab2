#include <stdio.h>

/*
 * `switch` is a keyword, not an identifier.  The compiler must reject this
 * declaration.  Build with:
 *
 *     gcc -std=c17 -Wall -Wextra -Wpedantic keyword_error.c -o keyword_error
 */
int main(void)
{
    int switch = 0;

    printf("%d\n", switch);
    return 0;
}
