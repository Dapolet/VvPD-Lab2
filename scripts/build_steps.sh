#!/usr/bin/env bash
#
# Walk through the compilation pipeline by hand:
#   .c -> .i -> .s -> .o -> executable
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT="$ROOT/artifacts/manual"
CC="${CC:-$(command -v gcc-16 || command -v gcc)}"
CFLAGS=(-std=c17 -Wall -Wextra -Wpedantic -O0 -g)

mkdir -p "$OUT"
cd "$ROOT"

echo "Compiler: $CC"
echo "Output:   $OUT"
echo

echo "[1/7] preprocess main.c -> main.i (line markers kept)"
"$CC" "${CFLAGS[@]}" -E main.c -o "$OUT/main.i"

echo "[2/7] preprocess main.c -> main_no_lines.i (-P suppresses line markers)"
"$CC" "${CFLAGS[@]}" -E -P main.c -o "$OUT/main_no_lines.i"

echo "[3/7] compile main.c -> main.s"
"$CC" "${CFLAGS[@]}" -S main.c -o "$OUT/main.s"

echo "[4/7] compile main.c -> main.o"
"$CC" "${CFLAGS[@]}" -c main.c -o "$OUT/main.o"

echo "[5/7] compile device.c -> device.o"
"$CC" "${CFLAGS[@]}" -c device.c -o "$OUT/device.o"

echo "[6/7] compile timer.c -> timer.o"
"$CC" "${CFLAGS[@]}" -c timer.c -o "$OUT/timer.o"

echo "[7/7] link main.o + device.o + timer.o -> vpd_lab2"
"$CC" "$OUT/main.o" "$OUT/device.o" "$OUT/timer.o" -o "$OUT/vpd_lab2"

echo
echo "Line-marker count in main.i: $(grep -c '^# ' "$OUT/main.i" || true)"
echo
echo "--- first 12 lines of main.i ---"
head -12 "$OUT/main.i"
echo
echo "--- first 12 lines of main_no_lines.i ---"
head -12 "$OUT/main_no_lines.i"
echo
echo "--- main symbol in main.s ---"
grep -n -A10 -E '^_?main:' "$OUT/main.s" | head -20
echo
echo "Manual executable built: $OUT/vpd_lab2"
