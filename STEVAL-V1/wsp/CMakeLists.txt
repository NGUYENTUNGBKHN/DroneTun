cmake_minimum_required(VERSION 3.20)

# Must be set BEFORE project() so toolchain is picked up
# Usage: cmake -B _cmake_build -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi.cmake

project(STEVAL-V1-wsp C ASM)

# --------------------------------------------------------------------------
# Global MCU flags (shared by all targets)
# --------------------------------------------------------------------------
set(MCU_CPU_FLAGS "-mcpu=cortex-m4 -mthumb --specs=nano.specs")
set(MCU_FPU_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16")
set(MCU_DEFINES   "-DSTM32F401xC")

# Convenient combined flag string (used by subdirectories via parent scope)
set(MCU_FLAGS "${MCU_CPU_FLAGS} ${MCU_FPU_FLAGS} $(MCU_DEFINES)" CACHE STRING "MCU compiler flags")

# Make CMAKE_OBJCOPY available to subdirectories
find_program(CMAKE_OBJCOPY arm-none-eabi-objcopy HINTS $ENV{TOOLCHAIN_TUNG})

# --------------------------------------------------------------------------
# Subdirectories — order matters (dependencies first)
# --------------------------------------------------------------------------
add_subdirectory(SDK)
add_subdirectory(Bootloader)
add_subdirectory(Middleware)


