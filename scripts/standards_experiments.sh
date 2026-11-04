#!/usr/bin/env bash
#
# Compile the same small probes under every ISO C mode supported by the
# selected compiler and record which features are accepted.
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
EXP="$ROOT/experiments"
OUT="$ROOT/artifacts/standards"
CC="${CC:-$(command -v gcc-16 || command -v gcc)}"
mkdir -p "$OUT"

run_case() {
    local name="$1"
    local std="$2"
    local src="$3"
    local bin="$OUT/${name}_${std}"
    local log="$OUT/${name}_${std}.log"

    printf '%-24s %-4s ' "$name" "$std"
    if "$CC" -std="$std" -Wall -Wextra -Wpedantic -pedantic-errors \
        "$EXP/$src" -o "$bin" >"$log" 2>&1; then
        echo "PASS"
        if [ -x "$bin" ]; then
            "$bin" >>"$log" 2>&1 || true
        fi
    else
        echo "FAIL"
    fi
}

if ! "$CC" -std=c23 -E -x c /dev/null >/dev/null 2>&1; then
    echo "warning: $CC does not accept -std=c23; C23 rows will fail" >&2
fi

echo "Compiler: $CC"
echo
run_case c99_features        c90 c99_features.c
run_case c99_features        c99 c99_features.c
run_case c11_static_assert   c99 c11_static_assert.c
run_case c11_static_assert   c11 c11_static_assert.c
run_case c23_binary          c17 c23_binary.c
run_case c23_binary          c23 c23_binary.c
run_case c23_auto            c17 c23_auto.c
run_case c23_auto            c23 c23_auto.c

echo
for std in c90 c99 c11 c17 c23; do
    run_case standard_probe "$std" standard_probe.c
    if [ -x "$OUT/standard_probe_${std}" ]; then
        "$OUT/standard_probe_${std}" | sed 's/^/    /'
    fi
done

echo
echo "Logs and binaries: $OUT"
