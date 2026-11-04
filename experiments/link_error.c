#include <stdio.h>

/*
 * device.c defines `internal` with internal linkage:
 *
 *     static unsigned long internal = 0;
 *
 * A declaration without `static` here promises external linkage, so the
 * compiler accepts this translation unit but the linker cannot find the
 * symbol.  Build this file together with device.c to see the failure:
 *
 *     gcc -std=c17 link_error.c ../device.c -o out/link_error
 */
extern unsigned long internal;

int main(void)
{
    printf("internal = %lu\n", internal);
    return 0;
}
