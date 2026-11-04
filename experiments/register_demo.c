#include <stdint.h>
#include <stdio.h>

enum RegisterBit {
    REG_POWER = 1u << 0,
    REG_READY = 1u << 1,
    REG_ERROR = 1u << 2,
    REG_TX    = 1u << 3,
    REG_RX    = 1u << 4
};

static void print_binary8(uint8_t value)
{
    for (int bit = 7; bit >= 0; --bit) {
        putchar((value & (1u << bit)) ? '1' : '0');
    }
}

static void print_register(const char *label, uint8_t reg)
{
    printf("%-14s dec=%3u hex=0x%02X bin=",
           label, (unsigned)reg, (unsigned)reg);
    print_binary8(reg);
    putchar('\n');
}

static uint8_t mask_of(unsigned bit)
{
    return (uint8_t)(1u << bit);
}

int main(void)
{
    uint8_t reg = 0;

    print_register("initial", reg);

    reg |= (uint8_t)REG_POWER;
    print_register("set POWER", reg);

    reg |= (uint8_t)REG_READY;
    print_register("set READY", reg);

    reg |= (uint8_t)REG_TX;
    print_register("set TX", reg);

    reg ^= (uint8_t)REG_ERROR;
    print_register("toggle ERROR", reg);

    printf("ERROR is set: %s\n", (reg & REG_ERROR) != 0 ? "yes" : "no");

    reg &= (uint8_t)~REG_ERROR;
    print_register("clear ERROR", reg);

    reg ^= (uint8_t)REG_READY;
    print_register("toggle READY", reg);

    reg |= mask_of(4);
    print_register("mask 1u << 4", reg);

    printf("RX is set: %s\n", (reg & REG_RX) != 0 ? "yes" : "no");

    return 0;
}
