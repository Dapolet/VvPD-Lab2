#include <stddef.h>
#include <stdio.h>

#define CHAR_COUNT 304
#define NUMBER_COUNT 25

static void print_char_table(const char *label, const char *data, size_t count)
{
    printf("%s (%zu elements, 10 per row):\n", label, count);
    for (size_t i = 0; i < count; ++i) {
        putchar(data[i]);
        if ((i + 1) % 10 == 0) {
            putchar('\n');
        }
    }
    if (count % 10 != 0) {
        putchar('\n');
    }
}

int main(void)
{
#ifdef UNINIT_DEMO
    /*
     * DANGER: reading an automatic object before it is initialized gives an
     * indeterminate value.  In C this can be undefined behavior.  The numbers
     * printed here are only what happened on this run; they are not a result
     * defined by the language and must not be used as a "memory leftovers"
     * technique.
     */
    puts("=== uninitialized automatic arrays (undefined behavior) ===");
    {
        char chars[CHAR_COUNT];
        int integers[NUMBER_COUNT];
        double reals[NUMBER_COUNT];

        printf("chars[0..7]    =");
        for (size_t i = 0; i < 8; ++i) {
            printf(" %d", chars[i]);
        }
        putchar('\n');

        printf("integers[0..7] =");
        for (size_t i = 0; i < 8; ++i) {
            printf(" %d", integers[i]);
        }
        putchar('\n');

        printf("reals[0..7]    =");
        for (size_t i = 0; i < 8; ++i) {
            printf(" %g", reals[i]);
        }
        putchar('\n');
        puts("The values above are indeterminate; reading them is not portable.");
    }
#endif

    puts("=== explicitly zero-initialized arrays ===");
    {
        char chars[CHAR_COUNT] = {0};
        int integers[NUMBER_COUNT] = {0};
        double reals[NUMBER_COUNT] = {0};

        for (size_t i = 0; i < CHAR_COUNT; ++i) {
            chars[i] = (char)('A' + (int)(i % 26));
        }
        for (size_t i = 0; i < NUMBER_COUNT; ++i) {
            integers[i] = (int)(i * i);
            reals[i] = (double)i / 4.0;
        }

        printf("chars:    sizeof=%zu, sizeof(element)=%zu, count=%zu\n",
               sizeof(chars), sizeof(chars[0]), sizeof(chars) / sizeof(chars[0]));
        printf("integers: sizeof=%zu, sizeof(element)=%zu, count=%zu\n",
               sizeof(integers), sizeof(integers[0]),
               sizeof(integers) / sizeof(integers[0]));
        printf("reals:    sizeof=%zu, sizeof(element)=%zu, count=%zu\n",
               sizeof(reals), sizeof(reals[0]),
               sizeof(reals) / sizeof(reals[0]));

        puts("\nintegers, one per line:");
        for (size_t i = 0; i < NUMBER_COUNT; ++i) {
            printf("%d\n", integers[i]);
        }

        puts("\nreals, one per line:");
        for (size_t i = 0; i < NUMBER_COUNT; ++i) {
            printf("%.2f\n", reals[i]);
        }

        putchar('\n');
        print_char_table("chars", chars, CHAR_COUNT);
    }

    return 0;
}
