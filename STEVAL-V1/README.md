

# Check available builder
## "MinGW Makefiles"
mingw32-make --version

## "Ninja"
ninja --version

## Visual Studio 
msbuild -version

# The first build

## 1. Configurate project
cmake -G "MinGW Makefiles" -B _cmake_build -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi.cmake

## 2. Build SDK
cmake --build _cmake_build --target stm32f401_lib -j4

## 3. Build Bootloader
cmake --build _cmake_build --target boot -j4
## Rebuild project
cmake --build _cmake_build --target boot --clean-first -j4

## 4. Build Middleware
cmake --build _cmake_build --target middleware -j4

## 5. Build Application
cmake --build _cmake_build --target app -j4
