cmake_minimum_required(VERSION 3.22)

project(Drivers)

add_library(${PROJECT_NAME}
STATIC
    STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
    STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
    STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
    STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
    #STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio_ex.c
    STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
    STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
    STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
    STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
    STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
)
target_compile_definitions(${PROJECT_NAME}
PUBLIC
    USE_HAL_DRIVER
    STM32F407xx
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    STM32F4xx_HAL_Driver/Inc
    STM32F4xx_HAL_Driver/Legacy
    CMSIS/Device/ST/STM32F4xx/Include
    CMSIS/Include
)
