# SDK — builds stm32f401_lib static library

add_library(stm32f401_lib STATIC)

# --------------------------------------------------------------------------
# Sources
# --------------------------------------------------------------------------
file(GLOB SDK_DEVICE_SRC   "${CMAKE_CURRENT_SOURCE_DIR}/Device/Src/*.c")
file(GLOB SDK_HAL_SRC      "${CMAKE_CURRENT_SOURCE_DIR}/Driver/hal/Src/*.c")
file(GLOB SDK_HAL_LEG_SRC  "${CMAKE_CURRENT_SOURCE_DIR}/Driver/hal/Src/Legacy/*.c")

target_sources(stm32f401_lib PRIVATE
    ${SDK_DEVICE_SRC}
    ${SDK_HAL_SRC}
    ${SDK_HAL_LEG_SRC}
)

# --------------------------------------------------------------------------
# Include directories (PUBLIC so dependents inherit them)
# --------------------------------------------------------------------------
target_include_directories(stm32f401_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/Include/Legacy
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/hal
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/hal/Include
)

# --------------------------------------------------------------------------
# Compile flags — same as SDK/Makefile (-O0 -g for library)
# --------------------------------------------------------------------------
target_compile_options(stm32f401_lib PRIVATE
    -mcpu=cortex-m4 -mthumb --specs=nano.specs
    -mfloat-abi=hard -mfpu=fpv4-sp-d16
    -O0 -g
    -DSTM32F401xC
)
