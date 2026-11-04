#ifndef DEVICE_H
#define DEVICE_H

#include <stdint.h>

/*
 * External linkage: the object below is defined once in device.c and is
 * visible to every translation unit that includes this header.
 */
extern unsigned long global_runs;

/* Bit positions of the model 8-bit device status register. */
enum RegisterBit {
    REG_POWER = 1u << 0,
    REG_READY = 1u << 1,
    REG_ERROR = 1u << 2,
    REG_TX    = 1u << 3,
    REG_RX    = 1u << 4
};

void device_reset(void);
void device_set(uint8_t mask);
void device_clear(uint8_t mask);
void device_toggle(uint8_t mask);
int  device_test(uint8_t mask);
uint8_t device_read(void);

void device_tick(void);
unsigned long device_internal_calls(void);
unsigned long device_static_calls(void);

void device_print_binary8(uint8_t value);

#endif /* DEVICE_H */
