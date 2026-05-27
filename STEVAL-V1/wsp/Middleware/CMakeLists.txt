# Middleware — builds middleware static library
# Equivalent to sources included inline in Application/Makefile

add_library(middleware STATIC)

# --------------------------------------------------------------------------
# Sources
# --------------------------------------------------------------------------
file(GLOB MID_MCU_SRC           "${CMAKE_CURRENT_SOURCE_DIR}/MCU/*.c")
file(GLOB MID_DEBUG_SRC         "${CMAKE_CURRENT_SOURCE_DIR}/Debug/*.c")
file(GLOB MID_BSP_SPBTLE_RF_SRC "${CMAKE_CURRENT_SOURCE_DIR}/BSP/Components/spbtle_rf/*.c")
file(GLOB MID_BLE_INTERFACE     "${CMAKE_CURRENT_SOURCE_DIR}/STM32_BlueNRG/Interface/*.c")
file(GLOB MID_BLE_HCI_CTRL      "${CMAKE_CURRENT_SOURCE_DIR}/STM32_BlueNRG/SimpleBlueNRG_HCI/hci/controller/*.c")
file(GLOB MID_BLE_HCI           "${CMAKE_CURRENT_SOURCE_DIR}/STM32_BlueNRG/SimpleBlueNRG_HCI/hci/*.c")
file(GLOB MID_BLE_UTILS         "${CMAKE_CURRENT_SOURCE_DIR}/STM32_BlueNRG/SimpleBlueNRG_HCI/utils/*.c")

target_sources(middleware PRIVATE
    ${MID_MCU_SRC}
    ${MID_DEBUG_SRC}
    ${MID_BSP_SPBTLE_RF_SRC}
    ${MID_BLE_INTERFACE}
    ${MID_BLE_HCI_CTRL}
    ${MID_BLE_HCI}
    ${MID_BLE_UTILS}
)

# --------------------------------------------------------------------------
# Include directories (PUBLIC so Application inherits them)
# --------------------------------------------------------------------------
target_include_directories(middleware PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/MCU
    ${CMAKE_CURRENT_SOURCE_DIR}/Debug
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32_BlueNRG/Interface
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32_BlueNRG/SimpleBlueNRG_HCI/includes
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP
    ${CMAKE_CURRENT_SOURCE_DIR}/BSP/Components/spbtle_rf
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