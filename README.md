# Лабораторная работа № 2

**Язык C изнутри: данные, управление, время выполнения и сборка проекта**

Проект содержит основной многофайловый C-проект, набор экспериментов по разделам
задания, Makefile для лабораторной № 1, ручную сборку и CMake-сборку.

## Окружение

| Инструмент | Версия |
|---|---|
| ОС | macOS 15.8.1 (24H32), arm64, Apple M1 Pro |
| GCC | Homebrew GCC 16.2.0 (`gcc-16`) |
| Apple Clang | 16.0.0 (clang-1600.0.26.6) |
| GNU Make | 3.81 |
| CMake | 4.4.5 |
| Ninja | 1.13.2 |

На macOS команда `gcc` по умолчанию указывает на Apple Clang. Makefile сам выбирает
`gcc-16`, если он установлен; иначе используется `cc`/`gcc`. Для C23-экспериментов
нужен компилятор с поддержкой `-std=c23` (в этом проекте — GCC 16).

## Структура

```text
VvPD-Lab2/
├── Makefile                 # сборка основного проекта, -O0/-O2, ручная сборка
├── CMakeLists.txt           # out-of-source сборка
├── main.c                   # стадии, прогресс-бар, таймеры, checksum
├── device.c / device.h      # регистр устройства, global/static/extern
├── timer.c / timer.h        # time(), clock(), gettimeofday()
├── experiments/             # небольшие программы по разделам задания
│   ├── Makefile
│   ├── types.c
│   ├── arrays.c
│   ├── ascii_arrays.c
│   ├── io_demo.c
│   ├── operators.c
│   ├── register_demo.c
│   ├── preprocessor.c
│   ├── standard_probe.c
│   ├── c99_features.c
│   ├── c11_static_assert.c
│   ├── c23_binary.c
│   ├── c23_auto.c
│   ├── link_error.c
│   ├── keyword_error.c
│   └── foreach.cpp
├── lab1/
│   ├── Makefile             # агрегирующий Makefile для ЛР1
│   └── laba1_all.txt        # вывод make run-all > laba1_all.txt
├── scripts/
│   ├── standards_experiments.sh
│   └── build_steps.sh
├── REPORT.md
└── .gitignore
```

## Быстрый старт

```bash
make                 # основной проект, -O0
make run             # собрать и запустить
make bench           # собрать варианты -O0 и -O2
make bench-run       # запустить оба варианта и сравнить
make manual          # .i, .s, .o и ручная линковка
make experiments     # собрать и запустить демонстрации
make standards       # матрица C90/C99/C11/C17/C23
make lab1            # собрать lab1/laba1_all.txt
```

По умолчанию одна стадия обрабатывает `5 500 000` значений по `64` раунда
смешивания. Полный прогон `-O0` занимает около 10 секунд. Размер можно изменить:

```bash
make ITEMS=1000000 ROUNDS=32
make run
```

## Основной проект

`main.c` реализует:

- `enum LabStage` и диспетчер через `switch`;
- стадии `for`, `while`, `do...while` и дополнительную стадию `bits`;
- progress bar через `\r` и `fflush(stdout)`;
- `uint64_t`-нагрузку (сдвиги, XOR, сложение) с итоговым `checksum`;
- маску завершённых частей `completed` с выводом в hex и binary;
- три таймера: `time()`/`difftime()`, `clock()`/`CLOCKS_PER_SEC`,
  `gettimeofday()` (на Windows — `QueryPerformanceCounter`).

`device.c` демонстрирует:

- `global_runs` с внешней связью (`extern` в `device.h`);
- `static internal` с внутренней связью (из `main.c` недоступен);
- `static` внутри `device_tick()` с временем жизни всей программы;
- 8-битный регистр: set/clear/toggle/test и двоичный вывод.

## CMake

```bash
cmake -S . -B build
cmake --build build
./build/vpd_lab2
```

`build/` — генерируемый каталог, в Git не коммитится. CMake не заменяет
компилятор: он только создаёт build-system для выбранного генератора.

## Ручная сборка

```bash
make manual
```

Скрипт `scripts/build_steps.sh` выполняет:

```text
gcc -E main.c -o main.i          # результат препроцессора
gcc -E -P main.c -o main_no_lines.i
gcc -S main.c -o main.s          # ассемблер
gcc -c main.c -o main.o          # объектный файл
gcc -c device.c -o device.o
gcc -c timer.c -o timer.o
gcc main.o device.o timer.o -o vpd_lab2
```

Результаты складываются в `artifacts/manual/`.

## Эксперименты

```bash
make -C experiments all
make -C experiments run
make -C experiments run-io
make -C experiments run-ub
make -C experiments link-error    # ожидаемая ошибка линковки
make -C experiments keyword-error # ожидаемая ошибка компилятора
```

`run-io` показывает корректный и некорректный ввод `scanf`. `run-ub` запускает
демонстрации с неопределённым поведением; их вывод — только наблюдение, а не
переносимый результат. `link-error` специально обращается к `static internal`
из `device.c` и показывает ошибку компоновки, а `keyword-error` — попытку
объявить переменную с именем `switch`.

## Makefile для лабораторной № 1

Makefile находится в `lab1/` и по умолчанию использует соседний проект
`../../VvPD-Lab1`:

```bash
make -C lab1 run-all > lab1/laba1_all.txt 2>&1
# или
make -C lab1 laba1_all.txt
```

Цели: `c`, `cpp`, `python`, `js`, `ts`, `java`, `csharp`, `fsharp`, `go`,
`rust`, `bash`, `prolog`, `asm`, агрегирующая `run-all` и `clean`. Команды
взяты из `VvPD-Lab1/scripts/run_all.sh`; для TypeScript сначала выполняется
`tsc`, затем запускается `dist/main.js`.

## Стандарты C

`scripts/standards_experiments.sh` проверяет:

| Возможность | Должна проходить |
|---|---|
| `//` и объявление `int i` в `for` | C99 |
| `_Static_assert` | C11 |
| двоичный литерал `0b...` | C23 |
| `auto x = 304` (вывод типа) | C23 |

Для каждого режима также собирается `standard_probe.c` и печатается
`__STDC_VERSION__`.

## Замечания

- Чтение неинициализированных автоматических объектов — indeterminate value,
  а во многих случаях undefined behavior. Числа в `arrays_uninit` не являются
  «правильным ответом».
- `a = b++ + ++b` не вычисляется: два неупорядоченных изменения одного объекта.
- `GOOD_SQUARE(i++)` — тоже UB, несмотря на «правильные» скобки.
- `%s` применим только к массиву `char`, завершённому `\0`.
- `CLOCKS_PER_SEC` — коэффициент перевода `clock_t` в секунды, а не частота CPU.
- `const` и `#define` — разные инструменты: типизированный объект против
  текстовой подстановки препроцессора.
