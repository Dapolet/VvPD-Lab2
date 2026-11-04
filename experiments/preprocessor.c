#include <stddef.h>
#include <stdio.h>

#define BUFFER_SIZE 304
const size_t buffer_size = 304;

#define BAD_SQUARE(x) x * x
#define GOOD_SQUARE(x) ((x) * (x))

#define STRINGIFY(x) #x
#define XSTRINGIFY(x) STRINGIFY(x)
#define CONCAT(a, b) a##b

#ifdef DEBUG
#  define DEBUG_LOG(msg) fprintf(stderr, "DEBUG: %s\n", msg)
#else
#  define DEBUG_LOG(msg) ((void)0)
#endif

int main(void)
{
    puts("=== const vs #define ===");
    printf("BUFFER_SIZE = %d, buffer_size = %zu\n", BUFFER_SIZE, buffer_size);
    puts("BUFFER_SIZE is a token replaced by the preprocessor;");
    puts("buffer_size is a typed const object with scope and lifetime.");

    puts("\n=== macro parentheses ===");
    printf("BAD_SQUARE(2 + 3)  = %d\n", BAD_SQUARE(2 + 3));
    printf("GOOD_SQUARE(2 + 3) = %d\n", GOOD_SQUARE(2 + 3));

    {
        int i = 5;
#ifdef RUN_UB_DEMO
        int result = GOOD_SQUARE(i++);
        printf("GOOD_SQUARE(i++) = %d, i = %d (undefined behavior)\n",
               result, i);
#else
        printf("GOOD_SQUARE(i++) not executed by default: it is UB\n");
        printf("i remains %d\n", i);
#endif
    }

    puts("\n=== stringify and token pasting ===");
    printf("STRINGIFY(BUFFER_SIZE)  = %s\n", STRINGIFY(BUFFER_SIZE));
    printf("XSTRINGIFY(BUFFER_SIZE) = %s\n", XSTRINGIFY(BUFFER_SIZE));

    {
        int CONCAT(var, 1) = 42;
        printf("CONCAT(var, 1) = var1 = %d\n", var1);
    }

    puts("\n=== conditional compilation ===");
    DEBUG_LOG("debug logging is enabled");
#ifdef DEBUG
    puts("DEBUG is defined: DEBUG_LOG expands to fprintf(stderr, ...)");
#else
    puts("DEBUG is not defined: DEBUG_LOG expands to ((void)0)");
#endif

    return 0;
}
