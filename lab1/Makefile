# Makefile for the Lab 1 multi-language project.
#
# The Lab 1 sources live in a sibling repository by default.  Override the
# location if yours is elsewhere:
#   make LAB1=/path/to/VvPD-Lab1 run-all
#
# On Windows with mingw32-make, replace "make" with "mingw32-make" as the
# laboratory manual requires.

LAB1 ?= ../../VvPD-Lab1

ifeq ($(origin CC),default)
CC := $(shell command -v gcc-16 >/dev/null 2>&1 && echo gcc-16 || echo cc)
endif
ifeq ($(origin CXX),default)
CXX := $(shell command -v g++-16 >/dev/null 2>&1 && echo g++-16 || echo c++)
endif

.PHONY: run-all c cpp python js ts java csharp fsharp go rust bash prolog asm clean

run-all: c cpp python js ts java csharp fsharp go rust bash prolog asm
	@echo
	@echo "===== ALL LANGUAGES DONE ====="

# A leading '-' keeps the aggregate run going when one toolchain is missing.
# The captured laba1_all.txt therefore records both successes and failures.

c:
	@echo "===== C ====="
	-@cd $(LAB1)/c && $(CC) -Wall -Wextra -pedantic main.c -o main && ./main

cpp:
	@echo "===== C++ ====="
	-@cd $(LAB1)/cpp && $(CXX) -Wall -Wextra -pedantic main.cpp -o main && ./main

python:
	@echo "===== Python ====="
	-@cd $(LAB1)/python && python3 main.py

js:
	@echo "===== JavaScript ====="
	-@cd $(LAB1)/javascript && node main.js

ts:
	@echo "===== TypeScript ====="
	-@cd $(LAB1)/typescript && tsc main.ts --outDir dist && node dist/main.js

java:
	@echo "===== Java ====="
	-@cd $(LAB1)/java && javac Main.java && java Main

csharp:
	@echo "===== C# ====="
	-@cd $(LAB1)/csharp && dotnet run --nologo

fsharp:
	@echo "===== F# ====="
	-@cd $(LAB1)/fsharp && dotnet run --nologo

go:
	@echo "===== Go ====="
	-@cd $(LAB1)/go && go run main.go

rust:
	@echo "===== Rust ====="
	-@cd $(LAB1)/rust && rustc main.rs -o main && ./main

bash:
	@echo "===== Bash ====="
	-@cd $(LAB1)/bash && bash main.sh

prolog:
	@echo "===== Prolog ====="
	-@cd $(LAB1)/prolog && swipl -q -s main.pl -g main -t halt

asm:
	@echo "===== Assembler ====="
	-@cd $(LAB1)/asm && bash build.sh && ./build/assembler

laba1_all.txt:
	$(MAKE) run-all > $@ 2>&1
	@echo "Wrote $@"

clean:
	-@rm -f $(LAB1)/c/main $(LAB1)/cpp/main $(LAB1)/rust/main
	-@rm -rf $(LAB1)/typescript/dist $(LAB1)/asm/build
	-@rm -f $(LAB1)/java/Main.class
	-@rm -rf $(LAB1)/csharp/bin $(LAB1)/csharp/obj
	-@rm -rf $(LAB1)/fsharp/bin $(LAB1)/fsharp/obj
	-@rm -f laba1_all.txt
