cmake_minimum_required(VERSION 3.28.3)
project(lc3plus VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_COMPILER "/home/max/work/zephyr-sdk-0.17.0/riscv64-zephyr-elf/bin/riscv64-zephyr-elf-gcc")
set(CMAKE_C_FLAGS "-DKERNEL -DK_HEAP_MEM_POOL_SIZE=0 -DNRF54L15_XXAA -DNRF_FLPR -DPICOLIBC_LONG_LONG_PRINTF_SCANF -DUSE_PARTITION_MANAGER=1 -D__LINUX_ERRNO_EXTENSIONS__ -D__ZEPHYR__=1 -fno-strict-aliasing -Os -O3 -ffast-math -Wno-array-bounds -DDISABLE_HR_MODE -DWMOPS=0 -DDONT_COUNT_MEM -fno-printf-return-value -fno-common -fdiagnostics-color=always -mabi=ilp32e -march=rv32emc_zicsr --sysroot=/home/max/work/zephyr-sdk-0.17.0/riscv64-zephyr-elf/riscv64-zephyr-elf -Wall -Wformat -Wformat-security -Wno-format-zero-length -Wdouble-promotion -Wno-pointer-sign -Wpointer-arith -Wexpansion-to-defined -Wno-unused-but-set-variable -Werror=implicit-int -fno-pic -fno-pie -fno-asynchronous-unwind-tables -ftls-model=local-exec -fno-reorder-functions --param=min-pagesize=0 -fno-defer-pop -ffunction-sections -fdata-sections -specs=picolibc.specs -std=c99")

include_directories(
    ../src/fixed_point
    ../src/fixed_point/basic_op
)

file(GLOB SOURCES
    ../src/fixed_point/basic_op/*.c
    ../src/fixed_point/*.c
)

add_library(lc3plus STATIC ${SOURCES})

set_target_properties(lc3plus PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

file(GLOB HEADERS
    ../src/fixed_point/basic_op/*.h
    ../src/fixed_point/*.h
)

# Create output include directory once
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include)

# Copy original headers to build dir and prepend #define
foreach(header ${HEADERS})
    get_filename_component(NAME_ONLY ${header} NAME)
    set(NEW_HEADER "${CMAKE_BINARY_DIR}/include/lc3plus/${NAME_ONLY}")
    file(READ "${header}" CONTENTS)
    set(NEW_CONTENTS "#define DISABLE_HR_MODE\n#define WMOPS 0\n#define DONT_COUNT_MEM\n${CONTENTS}")
    file(WRITE "${NEW_HEADER}" "${NEW_CONTENTS}")
endforeach()
