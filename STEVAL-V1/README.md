
# The first build

## 1. Configurate project
cmake -G "MinGW Makefiles" -B _cmake_build -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi.cmake

## 2. Build SDK
cmake --build _cmake_build --target stm32f401_lib -j4


