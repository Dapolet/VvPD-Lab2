cmake_minimum_required(VERSION 3.20)

project(VPD_Lab2 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(vpd_lab2
    main.c
    device.c
    timer.c
)

target_compile_options(vpd_lab2 PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
