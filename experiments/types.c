#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    puts("=== sizeof on this implementation ===");
    printf("char               %zu\n", sizeof(char));
    printf("signed char        %zu\n", sizeof(signed char));
    printf("unsigned char      %zu\n", sizeof(unsigned char));
    printf("short              %zu\n", sizeof(short));
    printf("unsigned short     %zu\n", sizeof(unsigned short));
    printf("int                %zu\n", sizeof(int));
    printf("unsigned int       %zu\n", sizeof(unsigned int));
    printf("long               %zu\n", sizeof(long));
    printf("unsigned long      %zu\n", sizeof(unsigned long));
    printf("long long          %zu\n", sizeof(long long));
    printf("unsigned long long %zu\n", sizeof(unsigned long long));
    printf("float              %zu\n", sizeof(float));
    printf("double             %zu\n", sizeof(double));
    printf("long double        %zu\n", sizeof(long double));
    printf("void *             %zu\n", sizeof(void *));
    printf("uint8_t            %zu\n", sizeof(uint8_t));
    printf("uint16_t           %zu\n", sizeof(uint16_t));
    printf("uint32_t           %zu\n", sizeof(uint32_t));
    printf("uint64_t           %zu\n", sizeof(uint64_t));

    puts("\n=== limits ===");
    printf("CHAR_BIT   = %d\n", CHAR_BIT);
    printf("SCHAR_MIN  = %d, SCHAR_MAX  = %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("UCHAR_MAX  = %u\n", (unsigned)UCHAR_MAX);
    printf("SHRT_MIN   = %d, SHRT_MAX   = %d\n", SHRT_MIN, SHRT_MAX);
    printf("USHRT_MAX  = %u\n", (unsigned)USHRT_MAX);
    printf("INT_MIN    = %d, INT_MAX    = %d\n", INT_MIN, INT_MAX);
    printf("UINT_MAX   = %u\n", UINT_MAX);
    printf("LONG_MIN   = %ld, LONG_MAX   = %ld\n", LONG_MIN, LONG_MAX);
    printf("ULONG_MAX  = %lu\n", ULONG_MAX);
    printf("LLONG_MIN  = %lld, LLONG_MAX  = %lld\n", LLONG_MIN, LLONG_MAX);
    printf("ULLONG_MAX = %llu\n", ULLONG_MAX);
    printf("UINT8_MAX  = %u\n", (unsigned)UINT8_MAX);
    printf("UINT16_MAX = %u\n", (unsigned)UINT16_MAX);
    printf("UINT32_MAX = %" PRIu32 "\n", UINT32_MAX);
    printf("UINT64_MAX = %" PRIu64 "\n", UINT64_MAX);

    puts("\n=== one value, three spellings ===");
    {
        int a = 304;
        int b = 0460;  /* octal */
        int c = 0x130; /* hexadecimal */

        printf("dec=%d oct=%o hex=%X\n", a, a, a);
        printf("a=%d b=%d c=%d, all equal: %s\n",
               a, b, c, (a == b && b == c) ? "yes" : "no");
    }

    puts("\n=== powers of two ===");
    for (int n = 0; n <= 20; ++n) {
        printf("2^%-2d = %" PRIu64 "\n", n, UINT64_C(1) << n);
    }
    printf("2^32 = %" PRIu64 "\n", UINT64_C(1) << 32);
    printf("2^48 = %" PRIu64 "\n", UINT64_C(1) << 48);
    printf("2^64 = 18446744073709551616 (does not fit uint64_t; UINT64_MAX = %" PRIu64 ")\n",
           UINT64_MAX);

    puts("\n=== binary units ===");
    printf("8 bit = 1 byte\n");
    printf("1 KiB = %d B\n", 1024);
    printf("1 MiB = %d KiB = %d B\n", 1024, 1024 * 1024);
    printf("1 GiB = %d MiB = %d KiB = %d B\n",
           1024, 1024 * 1024, 1024 * 1024 * 1024);
    puts("KiB/MiB/GiB are powers of 1024; kB/MB/GB are powers of 1000.");

    return 0;
}
