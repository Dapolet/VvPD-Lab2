#include <stdio.h>

int main(void)
{
    /*
     * Same character codes, four different element types.  The trailing zero
     * is added for the %s experiment; it does not turn the non-char arrays
     * into C strings.
     */
    char a[] = {'M', 'A', 'I', '3', '0', '4', '\0'};
    short b[] = {'M', 'A', 'I', '3', '0', '4', '\0'};
    int c[] = {'M', 'A', 'I', '3', '0', '4', '\0'};
    unsigned long long d[] = {'M', 'A', 'I', '3', '0', '4', '\0'};

    printf("char:               ");
    for (size_t i = 0; i + 1 < sizeof(a) / sizeof(a[0]); ++i) {
        printf("%c", a[i]);
    }
    putchar('\n');

    printf("short:              ");
    for (size_t i = 0; i + 1 < sizeof(b) / sizeof(b[0]); ++i) {
        printf("%c", (char)b[i]);
    }
    putchar('\n');

    printf("int:                ");
    for (size_t i = 0; i + 1 < sizeof(c) / sizeof(c[0]); ++i) {
        printf("%c", (char)c[i]);
    }
    putchar('\n');

    printf("unsigned long long: ");
    for (size_t i = 0; i + 1 < sizeof(d) / sizeof(d[0]); ++i) {
        printf("%c", (char)d[i]);
    }
    putchar('\n');

    printf("\nsizeof(a)=%zu sizeof(b)=%zu sizeof(c)=%zu sizeof(d)=%zu\n",
           sizeof(a), sizeof(b), sizeof(c), sizeof(d));
    printf("elements: a=%zu b=%zu c=%zu d=%zu\n",
           sizeof(a) / sizeof(a[0]), sizeof(b) / sizeof(b[0]),
           sizeof(c) / sizeof(c[0]), sizeof(d) / sizeof(d[0]));

    /*
     * %s expects a pointer to char followed by a null byte.  The casts below
     * make the byte-oriented experiment explicit.  On a little-endian machine
     * the first byte of each wide element is 'M', so %s usually prints "M".
     * This is not a valid way to store text.
     */
    printf("\n%%s on char array:               \"%s\"\n", a);
    printf("%%s on short array (cast):       \"%s\"\n", (const char *)b);
    printf("%%s on int array (cast):         \"%s\"\n", (const char *)c);
    printf("%%s on unsigned long long array: \"%s\"\n", (const char *)d);
    puts("Only the char array is a C string. The others are byte-level accidents.");

    return 0;
}
