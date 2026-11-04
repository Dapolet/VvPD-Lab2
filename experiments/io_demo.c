#include <stdio.h>

int main(void)
{
    int local = 0;

    puts("=== printf specifiers ===");
    printf("one integer: dec=%d oct=%o hex=%x HEX=%X\n",
           304, 304, 304, 304);
    printf("address of local variable: %p\n", (void *)&local);

    puts("\n=== escape sequences ===");
    printf("AAA\tBBB\n");
    printf("first\rSECOND\n");
    printf("one\0two\n");
    printf("quote: \"C\" and slash: \\\n");
    printf("bell follows (terminal-dependent): \a\n");

    puts("\nWhy only 'one' is visible on the \\0 line:");
    puts("printf stops at the first NUL because a C string ends there.");

    puts("\n=== scanf with validation ===");
    {
        int number = 0;
        unsigned int unsigned_number = 0;
        double real = 0.0;

        printf("Enter int, unsigned int, double: ");
        fflush(stdout);

        if (scanf("%d %u %lf", &number, &unsigned_number, &real) != 3) {
            fprintf(stderr,
                    "Invalid input: expected int, unsigned int, double\n");
            return 1;
        }

        printf("number=%d unsigned=%u real=%.3f\n",
               number, unsigned_number, real);
    }

    return 0;
}
