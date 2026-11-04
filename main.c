#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#include "device.h"
#include "timer.h"

/*
 * Work size is deliberately overridable from the command line:
 *   make ITEMS=1000000 ROUNDS=64
 * The defaults were tuned on the machine described in REPORT.md so that a
 * normal -O0 run takes roughly 8-15 seconds.
 */
#ifndef WORK_ITEMS
#define WORK_ITEMS UINT64_C(5500000)
#endif

#ifndef WORK_ROUNDS
#define WORK_ROUNDS 64u
#endif

enum LabStage {
    STAGE_FOR,
    STAGE_WHILE,
    STAGE_DO_WHILE,
    STAGE_BITS,
    STAGE_DONE
};

enum LabFlag {
    FLAG_TYPES  = 1u << 0,
    FLAG_ARRAYS = 1u << 1,
    FLAG_BITS   = 1u << 2,
    FLAG_FOR    = 1u << 3,
    FLAG_WHILE  = 1u << 4,
    FLAG_DO     = 1u << 5
};

static unsigned completed = 0;

static void print_progress(const char *stage, unsigned percent)
{
    const unsigned width = 30;
    unsigned filled = percent * width / 100;

    printf("\r%-12s [", stage);
    for (unsigned i = 0; i < width; ++i) {
        putchar(i < filled ? '#' : '-');
    }
    printf("] %3u%%", percent);
    fflush(stdout);
}

/*
 * The whole point of the inner loop is to keep a real, data-dependent
 * dependency chain.  A constant answer cannot be folded away because the
 * checksum is printed at the end.
 */
static uint64_t work_item(uint64_t index, uint64_t seed)
{
    uint64_t x = seed ^ (index + UINT64_C(0x9e3779b97f4a7c15));

    for (unsigned round = 0; round < WORK_ROUNDS; ++round) {
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        x += UINT64_C(0x9e3779b97f4a7c15);
    }
    return x;
}

static uint64_t stage_for(uint64_t seed)
{
    uint64_t checksum = 0;
    unsigned last = 100;

    for (uint64_t i = 0; i < WORK_ITEMS; ++i) {
        unsigned percent;

        checksum ^= work_item(i, seed);
        percent = (unsigned)(((i + 1) * 100) / WORK_ITEMS);
        if (percent != last) {
            print_progress("for", percent);
            last = percent;
        }
    }
    putchar('\n');
    return checksum;
}

static uint64_t stage_while(uint64_t seed)
{
    uint64_t checksum = 0;
    uint64_t i = 0;
    unsigned last = 100;

    while (i < WORK_ITEMS) {
        unsigned percent;

        checksum ^= work_item(i, seed);
        ++i;
        percent = (unsigned)((i * 100) / WORK_ITEMS);
        if (percent != last) {
            print_progress("while", percent);
            last = percent;
        }
    }
    putchar('\n');
    return checksum;
}

static uint64_t stage_do_while(uint64_t seed)
{
    uint64_t checksum = 0;
    uint64_t i = 0;
    unsigned last = 100;

    if (WORK_ITEMS == 0) {
        putchar('\n');
        return 0;
    }

    do {
        unsigned percent;

        checksum ^= work_item(i, seed);
        ++i;
        percent = (unsigned)((i * 100) / WORK_ITEMS);
        if (percent != last) {
            print_progress("do-while", percent);
            last = percent;
        }
    } while (i < WORK_ITEMS);

    putchar('\n');
    return checksum;
}

/*
 * Optional fourth stage: the loop is driven by the model device register.
 * It still processes WORK_ITEMS values and uses the result, so it is a real
 * computational stage rather than a decorative demo.
 */
static uint64_t stage_bits(uint64_t seed)
{
    static const uint8_t masks[] = {
        (uint8_t)REG_POWER,
        (uint8_t)REG_READY,
        (uint8_t)REG_ERROR,
        (uint8_t)REG_TX,
        (uint8_t)REG_RX
    };
    uint64_t checksum = 0;
    unsigned last = 100;

    device_reset();

    for (uint64_t i = 0; i < WORK_ITEMS; ++i) {
        uint8_t set_mask = masks[i % 5u];
        uint8_t test_mask = masks[(i + 1u) % 5u];
        uint8_t toggle_mask = masks[(i + 2u) % 5u];
        unsigned percent;

        device_set(set_mask);
        if (device_test(test_mask)) {
            device_toggle(toggle_mask);
        } else {
            device_clear(toggle_mask);
        }
        device_tick();
        checksum ^= work_item(i, seed ^ (uint64_t)device_read());

        percent = (unsigned)(((i + 1) * 100) / WORK_ITEMS);
        if (percent != last) {
            print_progress("bits", percent);
            last = percent;
        }
    }
    putchar('\n');
    return checksum;
}

static uint64_t run_pipeline(void)
{
    uint64_t checksum = 0;
    enum LabStage stage = STAGE_FOR;

    while (stage != STAGE_DONE) {
        switch (stage) {
        case STAGE_FOR:
            checksum ^= stage_for(UINT64_C(0x1111111111111111));
            completed |= FLAG_FOR;
            stage = STAGE_WHILE;
            break;
        case STAGE_WHILE:
            checksum ^= stage_while(UINT64_C(0x2222222222222222));
            completed |= FLAG_WHILE;
            stage = STAGE_DO_WHILE;
            break;
        case STAGE_DO_WHILE:
            checksum ^= stage_do_while(UINT64_C(0x3333333333333333));
            completed |= FLAG_DO;
            stage = STAGE_BITS;
            break;
        case STAGE_BITS:
            checksum ^= stage_bits(UINT64_C(0x4444444444444444));
            completed |= FLAG_BITS;
            stage = STAGE_DONE;
            break;
        case STAGE_DONE:
            break;
        }
    }
    return checksum;
}

static void demo_types(void)
{
    printf("sizeof(char)=%zu sizeof(int)=%zu sizeof(long)=%zu sizeof(void*)=%zu\n",
           sizeof(char), sizeof(int), sizeof(long), sizeof(void *));
    printf("INT_MIN=%d INT_MAX=%d UINT_MAX=%u\n",
           INT_MIN, INT_MAX, UINT_MAX);
    completed |= FLAG_TYPES;
}

static void demo_arrays(void)
{
    static const char text[] = {'M', 'A', 'I', '3', '0', '4', '\0'};

    printf("ASCII array: ");
    for (size_t i = 0; i + 1 < sizeof(text); ++i) {
        putchar(text[i]);
    }
    printf(" (sizeof=%zu, elements=%zu)\n",
           sizeof(text), sizeof(text) / sizeof(text[0]));
    completed |= FLAG_ARRAYS;
}

static void print_completed(void)
{
    const unsigned required =
        FLAG_TYPES | FLAG_ARRAYS | FLAG_BITS | FLAG_FOR | FLAG_WHILE | FLAG_DO;

    printf("completed = 0x%02X = ", completed);
    device_print_binary8((uint8_t)completed);
    printf("\nall required flags set: %s\n",
           (completed & required) == required ? "yes" : "no");
}

int main(void)
{
    TimerSnapshot start;
    uint64_t checksum;

    printf("VPD Lab 2: %" PRIu64 " items/stage, %u mixing rounds/item\n",
           (uint64_t)WORK_ITEMS, (unsigned)WORK_ROUNDS);

    demo_types();
    demo_arrays();

    timer_start(&start);
    checksum = run_pipeline();
    timer_stop(&start);

    printf("checksum = 0x%016" PRIx64 "\n", checksum);
    printf("global_runs = %lu\n", global_runs);
    printf("device_internal_calls = %lu\n", device_internal_calls());
    printf("device_static_calls = %lu\n", device_static_calls());
    print_completed();

    return 0;
}
