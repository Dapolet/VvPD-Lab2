ifeq ($(origin CC),default)
CC := $(shell command -v gcc-16 >/dev/null 2>&1 && echo gcc-16 || echo cc)
endif
ifeq ($(origin CXX),default)
CXX := $(shell command -v g++-16 >/dev/null 2>&1 && echo g++-16 || echo c++)
endif

CFLAGS ?= -std=c17 -Wall -Wextra -Wpedantic -O0 -g
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -O0 -g
OUT := out

C_BINS := $(OUT)/types $(OUT)/arrays $(OUT)/arrays_uninit $(OUT)/ascii_arrays \
          $(OUT)/io_demo $(OUT)/operators $(OUT)/register_demo \
          $(OUT)/preprocessor $(OUT)/preprocessor_debug \
          $(OUT)/preprocessor_ub $(OUT)/standard_probe
ALL_BINS := $(C_BINS) $(OUT)/foreach

.PHONY: all run run-io run-ub link-error clean help

all: $(ALL_BINS)

$(OUT):
	mkdir -p $@

$(OUT)/types: types.c | $(OUT)
	$(CC) $(CFLAGS) $< -o $@

$(OUT)/arrays: arrays.c | $(OUT)
	$(CC) $(CFLAGS) $< -o $@

$(OUT)/arrays_uninit: arrays.c | $(OUT)
	$(CC) $(CFLAGS) -DUNINIT_DEMO $< -o $@

$(OUT)/ascii_arrays: ascii_arrays.c | $(OUT)
	$(CC) $(CFLAGS) $< -o $@

$(OUT)/io_demo: io_demo.c | $(OUT)
	$(CC) $(CFLAGS) $< -o $@

$(OUT)/operators: operators.c | $(OUT)
	$(CC) $(CFLAGS) $< -o $@

$(OUT)/register_demo: register_demo.c | $(OUT)
	$(CC) $(CFLAGS) $< -o $@

$(OUT)/preprocessor: preprocessor.c | $(OUT)
	$(CC) $(CFLAGS) $< -o $@

$(OUT)/preprocessor_debug: preprocessor.c | $(OUT)
	$(CC) $(CFLAGS) -DDEBUG $< -o $@

$(OUT)/preprocessor_ub: preprocessor.c | $(OUT)
	$(CC) $(CFLAGS) -DRUN_UB_DEMO $< -o $@

$(OUT)/standard_probe: standard_probe.c | $(OUT)
	$(CC) $(CFLAGS) $< -o $@

$(OUT)/foreach: foreach.cpp | $(OUT)
	$(CXX) $(CXXFLAGS) $< -o $@

run: all
	@for exe in types arrays ascii_arrays operators register_demo \
	            preprocessor preprocessor_debug standard_probe; do \
	    echo "===== $$exe ====="; \
	    ./$(OUT)/$$exe; \
	    echo; \
	done
	@echo "===== foreach ====="; ./$(OUT)/foreach

run-io: $(OUT)/io_demo
	@echo "===== valid input ====="
	@printf '42 7 3.5\n' | ./$(OUT)/io_demo
	@echo "===== invalid input ====="
	@printf 'oops\n' | ./$(OUT)/io_demo; \
	    status=$$?; echo "exit status = $$status"

run-ub: $(OUT)/arrays_uninit $(OUT)/preprocessor_ub
	@echo "===== arrays_uninit (UB demonstration) ====="; ./$(OUT)/arrays_uninit
	@echo "===== preprocessor_ub (UB demonstration) ====="; ./$(OUT)/preprocessor_ub

# This target is expected to FAIL: `internal` has internal linkage in device.c.
link-error: | $(OUT)
	-$(CC) $(CFLAGS) link_error.c ../device.c -o $(OUT)/link_error

clean:
	rm -rf $(OUT)

help:
	@echo "make            build every experiment"
	@echo "make run        run the non-interactive experiments"
	@echo "make run-io     demonstrate valid and invalid scanf input"
	@echo "make run-ub     run the deliberately undefined-behavior demos"
	@echo "make clean      remove experiment binaries"
