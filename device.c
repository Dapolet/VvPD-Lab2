#include "device.h"

#include <stdio.h>

/*
 * External linkage: main.c sees this object through the extern declaration
 * in device.h.
 */
unsigned long global_runs = 0;

/*
 * Internal linkage: this name is visible only inside device.c.  Trying to
 * reference it from main.c fails at compile/link time, which is exactly the
 * isolation we want for the device state.
 */
static unsigned long internal = 0;

/* File-scope static state of the model register. */
static uint8_t reg = 0;

/*
 * A function-local static has static storage duration but block scope.
 * The pointer lets the test program inspect the counter without exposing
 * the variable itself.
 */
static unsigned long *calls_storage = NULL;

void device_reset(void)
{
    reg = 0;
}

void device_set(uint8_t mask)
{
    reg |= mask;
}

void device_clear(uint8_t mask)
{
    reg &= (uint8_t)~mask;
}

void device_toggle(uint8_t mask)
{
    reg ^= mask;
}

int device_test(uint8_t mask)
{
    return (reg & mask) != 0;
}

uint8_t device_read(void)
{
    return reg;
}

void device_tick(void)
{
    static unsigned long calls = 0; /* lives for the whole program */

    calls_storage = &calls;
    ++global_runs;
    ++internal;
    ++calls;
}

unsigned long device_internal_calls(void)
{
    return internal;
}

unsigned long device_static_calls(void)
{
    return calls_storage != NULL ? *calls_storage : 0;
}

void device_print_binary8(uint8_t value)
{
    for (int bit = 7; bit >= 0; --bit) {
        putchar((value & (1u << bit)) ? '1' : '0');
    }
}
