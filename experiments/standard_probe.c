#include <stdio.h>

int main(void)
{
#ifdef __STDC_VERSION__
    printf("__STDC_VERSION__ = %ld\n", (long)__STDC_VERSION__);
#else
    puts("__STDC_VERSION__ is not defined");
#endif

#ifdef __GNUC__
    printf("__GNUC__ = %d.%d.%d\n",
           __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif

#ifdef __clang__
    printf("__clang__ = %d.%d.%d\n",
           __clang_major__, __clang_minor__, __clang_patchlevel__);
#endif

    return 0;
}
