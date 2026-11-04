ifeq ($(origin CC),default)
CC := $(shell command -v gcc-16 >/dev/null 2>&1 && echo gcc-16 || echo cc)
endif

CFLAGS ?= -std=c17 -Wall -Wextra -Wpedantic -O0 -g
CPPFLAGS ?=
LDFLAGS ?=

ITEMS ?= 5500000
ROUNDS ?= 64
CPPFLAGS += -DWORK_ITEMS=$(ITEMS)ULL -DWORK_ROUNDS=$(ROUNDS)u

TARGET := vpd_lab2
OBJ := obj/main.o obj/device.o obj/timer.o
OBJ_O0 := obj/o0/main.o obj/o0/device.o obj/o0/timer.o
OBJ_O2 := obj/o2/main.o obj/o2/device.o obj/o2/timer.o
MANUAL := artifacts/manual

.PHONY: all run bench bench-run manual experiments standards lab1 clean help

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

obj/%.o: %.c | obj
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

obj/main.o: main.c device.h timer.h
obj/device.o: device.c device.h
obj/timer.o: timer.c timer.h

obj:
	mkdir -p $@

obj/o0/%.o: %.c | obj/o0
	$(CC) $(CPPFLAGS) $(CFLAGS) -O0 -c $< -o $@

obj/o2/%.o: %.c | obj/o2
	$(CC) $(CPPFLAGS) $(CFLAGS) -O2 -c $< -o $@

obj/o0/main.o: main.c device.h timer.h
obj/o0/device.o: device.c device.h
obj/o0/timer.o: timer.c timer.h
obj/o2/main.o: main.c device.h timer.h
obj/o2/device.o: device.c device.h
obj/o2/timer.o: timer.c timer.h

obj/o0:
	mkdir -p $@

obj/o2:
	mkdir -p $@

vpd_lab2_O0: $(OBJ_O0)
	$(CC) $(CFLAGS) -O0 $(LDFLAGS) $^ -o $@

vpd_lab2_O2: $(OBJ_O2)
	$(CC) $(CFLAGS) -O2 $(LDFLAGS) $^ -o $@

run: $(TARGET)
	./$(TARGET)

bench: vpd_lab2_O0 vpd_lab2_O2
	@echo "Built vpd_lab2_O0 and vpd_lab2_O2. Run 'make bench-run' to compare."

bench-run: bench
	@echo "===== -O0 ====="
	./vpd_lab2_O0
	@echo "===== -O2 ====="
	./vpd_lab2_O2

manual: | $(MANUAL)
	$(CC) $(CPPFLAGS) $(CFLAGS) -E main.c -o $(MANUAL)/main.i
	$(CC) $(CPPFLAGS) $(CFLAGS) -E -P main.c -o $(MANUAL)/main_no_lines.i
	$(CC) $(CPPFLAGS) $(CFLAGS) -S main.c -o $(MANUAL)/main.s
	$(CC) $(CPPFLAGS) $(CFLAGS) -c main.c -o $(MANUAL)/main.o
	$(CC) $(CPPFLAGS) $(CFLAGS) -c device.c -o $(MANUAL)/device.o
	$(CC) $(CPPFLAGS) $(CFLAGS) -c timer.c -o $(MANUAL)/timer.o
	$(CC) $(MANUAL)/main.o $(MANUAL)/device.o $(MANUAL)/timer.o -o $(MANUAL)/$(TARGET)
	@echo "Manual artifacts are in $(MANUAL)/"

$(MANUAL):
	mkdir -p $@

experiments:
	$(MAKE) -C experiments all
	$(MAKE) -C experiments run

standards:
	./scripts/standards_experiments.sh

lab1:
	$(MAKE) -C lab1 laba1_all.txt

clean:
	rm -rf obj build artifacts $(TARGET) vpd_lab2_O0 vpd_lab2_O2

help:
	@echo "make              build $(TARGET) with -O0"
	@echo "make run          build and run $(TARGET)"
	@echo "make bench        build -O0 and -O2 variants"
	@echo "make bench-run    build and run both variants"
	@echo "make manual       produce .i, .s, .o and link by hand"
	@echo "make experiments  build and run the small demos"
	@echo "make standards    run the C90..C23 feature matrix"
	@echo "make lab1         build Lab 1 Makefile output (laba1_all.txt)"
	@echo "make ITEMS=N ROUNDS=R   override workload size"
	@echo "make clean        remove generated build trees"
