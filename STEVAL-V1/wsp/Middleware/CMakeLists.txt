# Middleware — builds middleware static library
# Equivalent to sources included inline in Application/Makefile

add_library(middleware STATIC)

# --------------------------------------------------------------------------
# Sources
# --------------------------------------------------------------------------
file(GLOB MID_MCU_SRC       "${CMAKE_CURRENT_SOURCE_DIR}/MCU/*.c")
file(GLOB MID_DEBUG_SRC     "${CMAKE_CURRENT_SOURCE_DIR}/Debug/*.c")

target_sources(middleware PRIVATE
    ${MID_MCU_SRC}
    ${MID_DEBUG_SRC}
)

# --------------------------------------------------------------------------
# Include directories (PUBLIC so Application inherits them)
# --------------------------------------------------------------------------
target_include_directories(middleware PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/MCU
    ${CMAKE_CURRENT_SOURCE_DIR}/Debug
    ${CMAKE_SOURCE_DIR}/BSP
)

# --------------------------------------------------------------------------
# Compile flags
# --------------------------------------------------------------------------
target_compile_options(middleware PRIVATE
    -mcpu=cortex-m4 -mthumb --specs=nano.specs
    -mfloat-abi=hard -mfpu=fpv4-sp-d16
    -O3 -g3
    -ffunction-sections -fdata-sections
    -DSTM32F401xC
)

set_target_properties(middleware PROPERTIES PREFIX "")

# --------------------------------------------------------------------------
# Dependencies
# --------------------------------------------------------------------------
target_link_libraries(middleware PUBLIC stm32f401_lib)